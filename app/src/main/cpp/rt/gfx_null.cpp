// Backend "nulo": aceita tudo e nao desenha. Usado no teste de boot no PC e enquanto o GLES nao existe.
#include "gfx.h"
#include "rt.h"
#include <atomic>

struct NullGfx : GfxBackend {
    std::atomic<uint32_t> next{1};
    uint64_t frames = 0, draws = 0;
    bool init(int w, int h) override { rt_log("[gfx] backend nulo %dx%d\n", w, h); return true; }
    uint32_t tex_create(GfxTexType, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, bool) override { return next++; }
    void tex_upload(uint32_t, uint32_t, uint32_t, const uint8_t *, uint32_t) override {}
    void tex_destroy(uint32_t) override {}
    uint32_t buf_create(GfxBufKind, uint32_t) override { return next++; }
    void buf_upload(uint32_t, uint32_t, const uint8_t *, uint32_t) override {}
    void buf_destroy(uint32_t) override {}
    uint32_t vdecl_create(const uint8_t *, int) override { return next++; }
    uint32_t shader_create(bool, const uint32_t *, uint32_t) override { return next++; }
    void clear(const GfxDrawState &, uint32_t, uint32_t, float, uint32_t) override {}
    void draw(const GfxDrawState &, uint32_t, uint32_t, uint32_t, bool, int32_t, uint32_t, uint32_t) override { ++draws; }
    void draw_up(const GfxDrawState &, uint32_t, uint32_t, const uint8_t *, uint32_t, const uint8_t *, uint32_t, uint32_t) override { ++draws; }
    void present() override { if (++frames % 300 == 0) rt_log("[gfx] %llu quadros, %llu desenhos\n", (unsigned long long)frames, (unsigned long long)draws); }
};
GfxBackend *gfx_create_null() { return new NullGfx; }
GfxBackend *g_gfx = nullptr;
