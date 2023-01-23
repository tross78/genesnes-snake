
/**
 *  \typedef u8
 *      8 bits unsigned integer (equivalent to unsigned char).
 */
typedef unsigned char u8;
/**
 *  \typedef u16
 *      16 bits unsigned integer (equivalent to unsigned short).
 */
typedef unsigned short u16;
/**
 *  \typedef u32
 *      32 bits unsigned integer (equivalent to unsigned long).
 */
typedef unsigned long u32;

// u16 random(void);


// Constants
#define BUFFER_LENGTH 200
#define MAP_LENGTH 1120
#define SNAKE_START_LENGTH 3
#define SPEED_MIN 300
#define SPEED_MAX 10
#define APPLE_TILE 3

#define INT_MAX 65535



// Snake structure
typedef struct
{
    int x;
    int y;
    int index;
    int xVelocity;
    int yVelocity;
} SnakeSegment;

extern u16 map[];
extern int mapWidth;
extern int mapHeight;

int snakeLength;
SnakeSegment snake[100];

extern u16 inputUp;
extern u16 inputDown;
extern u16 inputLeft;
extern u16 inputRight;

int speed;
int score;
int gameOver;
int appleEaten;
int appleTimer;
int appleX;
int appleY;

extern unsigned int rx;
extern unsigned int ry;
extern unsigned int rz;
extern unsigned int rw;
extern unsigned int rc;

u16 appleIndex;
int x, y, i, j, a, b, c;

extern int main();
extern void initScreen();
extern void drawText(char* text, int x, int y);
extern void waitForInput();
extern u16 getInput();
extern void drawTileToXY(u16 tileIndex, u16 x, u16 y);
extern void blitMapToVideoRam();
extern void doVSync();
extern char* sprintScoreString(int score);
extern char* sprintInputString(int input);
extern char* sprintXString(int x);
extern char* sprintYString(int y);
extern int generateRandom(int max);