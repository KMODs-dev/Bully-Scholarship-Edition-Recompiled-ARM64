#include "x86rt.h"
#include "d3d9_com.h"
#include <map>
#include <mutex>
#include <string>
#include <vector>

static std::mutex g_mtx;
static std::map<std::string, uint32_t> g_vtables;
// objeto COM -> objeto do host: tabela em blocos, leitura sem trava (antes um mutex em TODA chamada D3D/D3DX)
#include <atomic>
static constexpr uint32_t HB = 4096, HN = 4096;   // ate 16M objetos
static std::atomic<void **> g_hblk[HN];
static std::atomic<uint32_t> g_hnext{1};

uint32_t com_vtable(const char *iface, const ComMethod *m, int n) {
    std::lock_guard<std::mutex> lk(g_mtx);
    auto it = g_vtables.find(iface);
    if (it != g_vtables.end()) return it->second;
    const uint32_t vt = rt_alloc(4u * (uint32_t)n, true);
    for (int i = 0; i < n; ++i) {
        std::string full = std::string(iface) + "::" + (m[i].name ? m[i].name : "?");
        wr32(vt + 4u * i, rt_make_thunk(strdup(full.c_str()), m[i].nargs + 1, m[i].fn));
    }
    g_vtables[iface] = vt;
    return vt;
}
uint32_t com_new(uint32_t vtable, void *host) {
    uint32_t id;
    {
        std::lock_guard<std::mutex> lk(g_mtx); id = g_hnext.load(std::memory_order_relaxed);
        if (id >= HB * HN) rt_fatal("objetos COM demais\n");
        void **b = g_hblk[id / HB].load(std::memory_order_relaxed);
        if (!b) { b = new void *[HB](); g_hblk[id / HB].store(b, std::memory_order_release); }
        __atomic_store_n(&b[id % HB], host, __ATOMIC_RELEASE);
        g_hnext.store(id + 1, std::memory_order_release);
    }
    const uint32_t o = rt_alloc(16, true);
    wr32(o, vtable); wr32(o + 4, id); wr32(o + 8, 1);
    return o;
}
void *com_host(uint32_t obj) {
    if (!obj) return nullptr;
    const uint32_t id = rd32(obj + 4);
    if (id >= g_hnext.load(std::memory_order_acquire)) return nullptr;
    void **b = g_hblk[id / HB].load(std::memory_order_acquire);
    return b ? __atomic_load_n(&b[id % HB], __ATOMIC_ACQUIRE) : nullptr;
}
uint32_t com_addref(uint32_t obj) { return __atomic_add_fetch((uint32_t *)(M + obj + 8), 1u, __ATOMIC_SEQ_CST); }
uint32_t com_release(uint32_t obj) { return __atomic_sub_fetch((uint32_t *)(M + obj + 8), 1u, __ATOMIC_SEQ_CST); }
