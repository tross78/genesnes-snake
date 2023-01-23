

#include <genesis.h>
#include "resources.h"
#include "common.h"

int mapWidth = 40;
int mapHeight = 28;

u16 map[MAP_LENGTH];


u16 inputUp = 0x0001;
u16 inputDown = 0x0002;
u16 inputLeft = 0x0004;
u16 inputRight = 0x0008;

#define MAP_LENGTH 1120

void initScreen()
{
    VDP_setScreenWidth320();
    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    // Load the tile set
    VDP_loadTileSet(appleTiles.tileset, TILE_USER_INDEX, DMA);
    PAL_setColors(0, (u16 *)appleTiles.palette->data, 16, CPU);
}

void drawTileToXY(u16 tileIndex, u16 x, u16 y)
{

    // Calculate the tile address
    u16 tileAddress = TILE_USER_INDEX + tileIndex;
    VDP_setTileMapXY(BG_B, tileAddress, x, y);
}

void drawText(char *text, int x, int y)
{
    // Draw the text to the screen
    VDP_drawText(text, x, y);
}

u16 getInput()
{
    return JOY_readJoypad(JOY_1);
}

void blitMapToVideoRam() {

}

void doVSync()
{
    // Wait for vertical sync
    VDP_waitVSync();
    SYS_doVBlankProcess();
}

char* sprintScoreString(int score)
{
    // Convert the score to a string
    static char scoreString[16];
    sprintf(scoreString, "SCORE: %d", score);
    return scoreString;
}

char* sprintXString(int num)
{
    // Convert the score to a string
    static char strStr[16];
    sprintf(strStr, "X: %u", num);
    return strStr;
}


char* sprintYString(int num)
{
    // Convert the score to a string
    static char strStr[16];
    sprintf(strStr, "Y: %u", num);
    return strStr;
}

int generateRandom(int max)
{
    return random() % max;
}