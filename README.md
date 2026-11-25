# Bully PC para Android (recompilação estática)

Port do **Bully: Scholarship Edition** (versão de PC 1.200) para Android ARM64. O jogo não é emulado: o código x86 do
`Bully.exe` é traduzido para C++ e compilado nativamente para ARM64. As partes do Windows que o jogo usa (Direct3D 9,
XACT3, DirectInput/XInput, arquivos, threads, registro) foram reescritas sobre OpenGL ES 3.2, FAudio e SDL2.

> **Este repositório não contém o jogo.** Para jogar é preciso ter uma cópia original do Bully: Scholarship Edition de
> PC (exe 1.200) e copiar os arquivos do jogo para o aparelho.

## Download e instalação (para jogar)

1. Baixe o APK mais recente na página de
   **[Releases](https://github.com/KMODs-dev/Bully-Scolarship-Edition-Recompiled-ARM64/releases)** e instale
   (permita "instalar apps de fontes desconhecidas" se o Android pedir).
2. Copie a pasta do Bully: Scholarship Edition **de PC, versão 1.200**, já instalado, para
   `Android/data/com.bully.pc/files/Bully` no celular (ou escolha outra pasta no launcher).
3. Abra o app. No launcher, escolha a resolução, as sombras, o limite de FPS e a tela cheia, e toque em **JOGAR**.
4. Se algo der errado, o log fica em `Android/data/com.bully.pc/files/bully-log.txt`. Anexe esse arquivo ao abrir
   uma issue.

Dicas para o Helio G85 / Mali-G52: sombras desligadas, limite de 30 FPS e uma resolução 16:9 (1066x600 ou
1280x720) com a tela cheia ligada.

## Como funciona

| Parte | Onde | O que faz |
|---|---|---|
| Recompilador | `tools/x86rc.py` | Lê o `Bully.exe` (PE 32 bits) e a desmontagem do `objdump` e gera uma função C++ por função do jogo (`gen/bully_NNN.cpp`, `tables.cpp`). Cache do x87 em variáveis, registradores em locais, tabelas de salto, funções achadas por vtable. |
| Correções do SilentPatch | `tools/sp_patch.py`, `rt/silentpatch.cpp` | Correções do SilentPatchBully (CookiePLMonster) refeitas para o port: colisão, Nutcrackin', pools de objetos, vazamento de memória dos bancos de som, limite de FPS configurável. |
| Runtime Win32 | `rt/rt_win32.cpp`, `rt/rt_core.cpp`, `rt/rt_thread.cpp` | Kernel32/User32/etc.: arquivos, threads, eventos, heap, registro (gravado em `registro.txt`), despacho das chamadas. |
| Gráficos | `rt/d3d9.cpp`, `rt/d3dx9_effect.cpp`, `rt/sm_translate.cpp`, `rt/gfx_gl.cpp`, `rt/gfx_mt.cpp` | Direct3D 9 + efeitos D3DX sobre OpenGL ES 3.2. Shaders SM2/SM3 traduzidos para GLSL ES, cache de programas em disco, render numa thread própria. |
| Áudio | `rt/xact3.cpp` + `faudio/` | XACT3 sobre FACT/FAudio. |
| Controles | `rt/input.cpp`, `rt/dinput8.cpp` | Controle físico (XInput) e controles na tela no estilo do Xbox 360. |
| App Android | `app/src/main/java/com/bully/pc/` | Launcher (pasta do jogo, resolução, sombras, limite de FPS, opções de tela) e a activity do jogo (SDL2). |

## Desempenho (moto g24: Helio G85, Mali-G52 MC2, Android 14)

Medido com o log do próprio port (`bully-log.txt`), na escola, a 1280x720:

| Situação | Thread do jogo | FPS |
|---|---|---|
| Sombras desligadas | ~33–42 ms | **~25–30** |
| Sombras médias | ~39–57 ms | ~18–25 |

- **O limite é a CPU, não a GPU.** A Mali-G52 termina cada quadro em ~1 ms, por isso mudar a resolução quase não muda
  o FPS. O tempo vai no código do jogo e nas chamadas gráficas (~600 desenhos por quadro, cada um com várias chamadas de
  efeito D3DX).
- Os 2 núcleos rápidos (Cortex-A75, 2,0 GHz) rodam a thread do jogo e a do render; os 6 núcleos A55 quase não ajudam.
- Limite de 30 FPS recomendado. A opção de 60 FPS existe, mas este aparelho não chega lá.
- Mali-G52: sem filtro linear em texturas float32 (`OES_texture_float_linear`) e sem DXT, que é decodificado na CPU
  na primeira carga.

## Requisitos

- Android 8+ ARM64, GPU com OpenGL ES 3.2 (testado na Mali-G52).
- Bully: Scholarship Edition de PC, **exe versão 1.200**, com os arquivos do jogo instalados.
- Para compilar no celular: [AndroidIDE](https://github.com/AndroidIDEOfficial/AndroidIDE) com NDK e CMake.
  No PC, Android Studio com NDK também funciona.
- Para regerar o código traduzido: Linux ou WSL com Python 3 e `objdump` (binutils).

## Como compilar (para desenvolvedores)

Só é preciso para quem quer modificar o port. Para jogar, use o APK dos Releases.

1. **Gerar o código traduzido a partir do seu exe** (o `gen/` não vai no repositório):
   ```sh
   python3 tools/sp_patch.py Bully.exe Bully_sp.exe dis_original.txt   # dis_original.txt = objdump do Bully.exe original
   objdump -d --no-show-raw-insn -M intel Bully_sp.exe > dis_sp.txt
   BULLY_CHUNK=1000000 python3 tools/x86rc.py Bully_sp.exe dis_sp.txt app/src/main/cpp/gen
   ```
   Copie também `x86rt.h` para `app/src/main/cpp/gen/`.
2. **SDL2**: aponte `bully.sdl2` no `gradle.properties` para o código-fonte do SDL2 (2.32.x).
3. **Compilar**: abra o projeto no AndroidIDE e gere o APK. A primeira compilação é longa (são ~114 arquivos grandes
   do `gen/`). Se o AndroidIDE fechar por falta de memória, troque `BULLY_JOBS` para `"1"` no
   `app/src/main/cpp/CMakeLists.txt`.
4. **Arquivos do jogo**: copie a pasta do Bully instalado no PC para
   `Android/data/com.bully.pc/files/Bully` (ou escolha outra pasta no launcher).
5. Abra o app, escolha resolução, sombras e limite de FPS no launcher e toque em **JOGAR**.
   O log fica em `Android/data/com.bully.pc/files/bully-log.txt`.

## Problemas conhecidos

- **Sombras piscando** (o mapa de sombra parece falhar em alguns quadros). Causas já descartadas: filtro linear em
  float32, erro de GL no mapa, conflito entre as threads. Por enquanto, desligue as sombras no launcher.
- Com sombras o FPS cai para ~18–25 (custo de CPU: os personagens são desenhados duas vezes).
- Primeiro carregamento lento (shaders e texturas são convertidos e guardados em cache).

## Próximos passos

- Cheats no launcher (dinheiro, vida, munição infinita, armas), usando os códigos oficiais pelo controle virtual.
- Corrigir o pisca-pisca das sombras.
- Reduzir o custo das chamadas de efeito (BeginPass, SetVector) na thread do jogo.
- Controles na tela personalizáveis (posição, tamanho, transparência).

## Créditos e licenças

- **Bully: Scholarship Edition** © Rockstar Games / Take-Two. Nenhum arquivo do jogo, nem código traduzido dele, é
  distribuído aqui.
- **SilentPatchBully** — CookiePLMonster (as correções foram reimplementadas a partir do código-fonte público; veja a
  licença do projeto original).
- **FAudio/FACT** — licença zlib (`faudio/LICENSE`). **SDL2** — licença zlib.
