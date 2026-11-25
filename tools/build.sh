#!/bin/sh
# regenera o C, compila e roda o teste de boot no PC
cd "$(dirname "$0")"
[ "$1" = "gen" ] && { rm -rf out; python3 x86rc.py /mnt/user-data/attachments/f174b2bc-b4b7-5724-a62f-868da52ebe4d/d3a89191-Bully.exe dis.txt out > gen.log 2>&1; rm -rf obj; }
mkdir -p obj; cp rt/*.cpp rt/rt.h x86rt.h out/
cd out
for f in *.cpp; do [ ../obj/$f.o -nt $f ] && [ ../obj/$f.o -nt x86rt.h ] || echo $f; done | xargs -r -P 2 -I{} sh -c 'g++ -std=c++17 -O1 -w -c {} -o ../obj/{}.o 2>&1 | grep -m3 error'
cd ../obj; g++ -o ../bully_pc *.o -lm -lpthread 2>&1 | grep -v warning | head -5
cd ..; timeout 60 ./bully_pc /mnt/user-data/attachments/f174b2bc-b4b7-5724-a62f-868da52ebe4d/d3a89191-Bully.exe gamedir 2>&1 | grep -v GetProcAddress | tail -15
