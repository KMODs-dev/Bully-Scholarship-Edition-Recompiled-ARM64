cmake_minimum_required(VERSION 3.22)
project(bullypc C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SDL2_DIR "" CACHE PATH "fonte do SDL2")
if(NOT SDL2_DIR)
    message(FATAL_ERROR "Defina bully.sdl2 no gradle.properties")
endif()
# otimizacao do codigo recompilado (gen/): -O1 compila bem mais rapido; -O2 roda um pouco mais rapido
set(BULLY_GEN_OPT "-O1")   # -O2: ~10-25% mais rapido no codigo do jogo, mas compila bem mais devagar
# Celular: limita quantos arquivos compilam ao mesmo tempo (cada um usa bastante RAM; muitos juntos fecham o AndroidIDE)
set(BULLY_JOBS "2" CACHE STRING "compilacoes em paralelo")
set_property(GLOBAL PROPERTY JOB_POOLS compila=${BULLY_JOBS} liga=1)
set(CMAKE_JOB_POOL_COMPILE compila)
set(CMAKE_JOB_POOL_LINK liga)

add_subdirectory(${SDL2_DIR} SDL2-build EXCLUDE_FROM_ALL)

file(GLOB GEN_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/gen/*.cpp")
file(GLOB RT_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/rt/*.cpp")
list(FILTER RT_SRC EXCLUDE REGEX "main_pc\\.cpp$")

# FAudio/FACT (reimplementacao aberta do XACT3, licenca zlib: faudio/LICENSE): toca o audio do jogo via SDL2
file(GLOB FAUDIO_SRC "${CMAKE_CURRENT_SOURCE_DIR}/faudio/src/*.c")
list(FILTER FAUDIO_SRC EXCLUDE REGEX "(win32|sdl3|XNA_Song)")
add_library(faudio STATIC ${FAUDIO_SRC})
target_include_directories(faudio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/faudio/include PRIVATE ${SDL2_DIR}/include)
target_compile_definitions(faudio PRIVATE DISABLE_XNASONG FAUDIO_DISABLE_DEBUGCONFIGURATION)
target_compile_options(faudio PRIVATE -O2 -g0 -w -include string.h)
target_link_libraries(faudio PRIVATE SDL2)

add_library(main SHARED android_main.cpp gfx_gles.cpp ${RT_SRC} ${GEN_SRC})
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/rt ${CMAKE_CURRENT_SOURCE_DIR}/gen ${SDL2_DIR}/include)
# o codigo gerado imita o x86: sem FMA (mul+add separados) e sem suposicoes de aliasing
set_source_files_properties(${GEN_SRC} PROPERTIES COMPILE_OPTIONS "${BULLY_GEN_OPT};-g0;-w;-ffp-contract=off;-fno-strict-aliasing")
# arquivos do gen/ com as funcoes que mais pesam no perfil do aparelho (as ~40 primeiras): -O2 so neles.
# A lista vale para o gen da versao 2.1 (gerado com BULLY_CHUNK=1000000); se o gen for regerado, refazer a lista.
set(BULLY_GEN_HOT 003 005 007 023 025 029 033 034 060 062 071 072 073 074 077 083 095 096 097 098 101 102 107)
foreach(n ${BULLY_GEN_HOT})
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/gen/bully_${n}.cpp" PROPERTIES COMPILE_OPTIONS "-O2;-g0;-w;-ffp-contract=off;-fno-strict-aliasing")
endforeach()
# -g0: sem informacao de depuracao (no build debug ela multiplica a RAM usada e o tamanho do .so)
target_compile_options(main PRIVATE -O2 -g0 -ffp-contract=off -fno-strict-aliasing)
target_link_libraries(main PRIVATE faudio SDL2 SDL2main GLESv3 EGL android log m)
target_link_options(main PRIVATE -Wl,-Bsymbolic -Wl,--threads=1 -s)
