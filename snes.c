
#define MAP_LENGTH      928

#include <snes.h>
#include "common.h"
#include <string.h>

u16 blockmap[0x400];
u8 blocks[0x400];

int mapWidth = 32;
int mapHeight = 29;

u16 map[MAP_LENGTH] = {0};

u16 inputUp = 2048;
u16 inputDown = 1024;
u16 inputLeft = 512;
u16 inputRight = 256;


extern char tileset, tilesetend, tilepal;
extern char snesfont, snespal;

void initScreen()
{

 // Initialize SNES
    consoleInit();
    // // Initialize text console with our font
    consoleSetTextVramBGAdr(0x6000);
    consoleSetTextVramAdr(0x3000);
    consoleInitText(1, 16 * 2 * 3, &snesfont, &snespal);

    for (j = 0; j < 29; j++)
    {
        for (i = 0; i < 32; i++)
        {
            u16 mapIndex = j*mapWidth+i;
            u16 tileX = mapIndex % mapWidth;
            u16 tileY = mapIndex / mapWidth;
            u16 tileIndex = map[mapIndex];
            drawTileToXY(tileIndex, tileX, tileY);
        }
    }

    bgSetGfxPtr(1, 0x3000);
    bgSetMapPtr(1, 0x6000, SC_32x32);

    bgInitTileSet(0, &tileset, &tilepal, 1, (&tilesetend - &tileset), 16 * 2 * 3, BG_16COLORS, 0x4000);
    // Copy Map to VRAM
    bgInitMapSet(0, (u8 *)blockmap, 0x800, SC_32x32, 0x0000);

    setMode(BG_MODE1, 0);

    bgSetDisable(2);
        // Wait for nothing :P
    setBrightness(0xF);
    setScreenOn();
}

void drawText(char* text, int x, int y)
{
    // Draw the text to the screen
    consoleDrawText(x, y, text);
}

void doVSync() {
    WaitForVBlank();
}

u16 getInput() {
    return padsCurrent(0);
}

void drawTileToXY(u16 tileIndex, u16 x, u16 y)
{ 
    a = tileIndex;
    c = (y << 5) + x;
    blockmap[c] = a + (1 << 10);
}

char* sprintScoreString(int score)
{
    // Convert the score to a string
    static char scoreString[16];
    sprintf(scoreString, "SCORE: %d", score);
    return scoreString;
}

char* sprintInputString(int input)
{
    // Convert the score to a string
    static char inputString[16];
    sprintf(inputString, "INPUT: %u", input);
    return inputString;
}

void blitMapToVideoRam() {
    WaitForVBlank();
    dmaCopyVram((u8 *)blockmap, 0x0000, 0x800);
}


int generateRandom(int max)
{
    int t;
    ry ^= (ry << 5);
    ry ^= (ry >> 7);
    ry ^= (ry << 22);
    t = rz + rw + rc;
    rz = rw;
    rc = t < 0;
    rw = t & 2147483647;
    rx += 1411392427;
    return (rx + ry + rw) % max;
}