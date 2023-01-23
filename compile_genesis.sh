rm -rf genesis/src
rm -rf roms
mkdir roms
mkdir genesis/src
mkdir genesis/src/boot
cp genesis.c genesis/src/main.c
cp common.c genesis/src/common.c
cp common.h genesis/src/common.h
cd genesis
docker run --rm -v "$PWD":/m68k -t -u $(id -u):$(id -g) registry.gitlab.com/doragasu/docker-sgdk:v1.80 release
cp out/rom.bin ../roms/rom.md
dgen ../roms/rom.md