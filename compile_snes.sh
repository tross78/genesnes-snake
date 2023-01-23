rm -rf snes/main.c
rm -rf snes/common.c
rm -rf snes/common.h
rm -rf roms
mkdir roms
cp snes.c snes/main.c
cp common.c snes/common.c
cp common.h snes/common.h
cd snes
docker run --rm -v "${PWD}":/src/ -it bensuperpc/pvsneslib \
make all \
exit
cp main.sfc ../roms/rom.sfc
OPEN -a /Applications/bsnes.app --args /Users/tysonross/Documents/GitHub/megadrive-snes/roms/rom.sfc