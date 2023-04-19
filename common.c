
#include "common.h"

int buffer[BUFFER_LENGTH] = {-1};
unsigned int rx=123456789;
unsigned int ry=234567891;
unsigned int rz=345678912;
unsigned int rw=456789123;
unsigned int rc=0;

u16 getIndexFromXY(u16 x, u16 y)
{
    return y * mapWidth + x;
}

void addToRedrawBuffer(int mapIndex)
{

    // shift all tiles in the buffer along
    for (j = BUFFER_LENGTH - 1; j > 0; j--)
    {
        buffer[j] = buffer[j - 1];
    }
    // push new tileIndex to the front
    buffer[0] = mapIndex;
}

void setMapTile(u16 mapIndex, int tileIndex)
{
    map[mapIndex] = (u16)tileIndex;
    addToRedrawBuffer(mapIndex);
}

void drawMapTile(u16 mapIndex)
{
    u16 tileX = mapIndex % mapWidth;
    u16 tileY = mapIndex / mapWidth;
    u16 tileIndex = map[mapIndex];
    drawTileToXY(tileIndex, tileX, tileY);
}

void updateSnake()
{
    // int oldIndex[snakeLength];

    // set the old snake positions to dirty
    for (i = 0; i < snakeLength; i++)
    {
        setMapTile(getIndexFromXY(snake[i].x, snake[i].y), 0);
    }

    // Update the snake segments
    for (i = snakeLength - 1; i > 0; i--)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
        snake[i].index = snake[i].y * mapWidth + snake[i].x;
    }

    // Update the head position
    snake[0].x += snake[0].xVelocity;
    snake[0].y += snake[0].yVelocity;
    snake[0].index = snake[0].y * mapWidth + snake[0].x;

    // Wrap the snake around the edges of the map
    if (snake[0].x >= mapWidth)
    {
        snake[0].x = 0;
    }
    else if (snake[0].x < 0)
    {
        snake[0].x = mapWidth - 1;
    }
    if (snake[0].y >= mapHeight)
    {
        snake[0].y = 0;
    }
    else if (snake[0].y < 0)
    {
        snake[0].y = mapHeight - 1;
    }

    // Draw the snake to the map
    for (i = 0; i < snakeLength; i++)
    {
        snake[i].index = snake[i].y * mapWidth + snake[i].x;
        setMapTile(getIndexFromXY(snake[i].x, snake[i].y), 1);
    }
}


// Function to init and draw the map
void drawMap()
{
    for (i = 0; i < MAP_LENGTH; i++)
    {
        drawMapTile((u16)i);
    }
}

// Function to update the apple
void updateApple()
{

    // Check if the apple has been eaten
    if (appleEaten)
    {
        // clear old apple spot
        setMapTile(appleIndex, 0);
        //  Generate a new apple position
        appleX = generateRandom(mapWidth - 1);
        appleY = generateRandom(mapHeight - 1);

    
        // Set the apple tile in the map
        appleIndex = appleY * mapWidth + appleX;

        setMapTile(appleIndex, APPLE_TILE);

        doVSync();
        // Reset the apple timer
        appleTimer = 0;

        // Set the apple eaten flag to false
        appleEaten = 0;
    }
    else
    {
        // Increment the apple timer
        appleTimer++;

        // Check if it's time to remove the apple
        if (appleTimer >= speed)
        {
            // Set the apple tile in the map
            appleIndex = appleY*mapWidth+appleX;
            // Remove the apple from the map
            setMapTile(appleIndex, 0);
            // Set the apple eaten flag to true
            appleEaten = 1;
        }
    }
}

// Function to init and draw the map
void drawBuffer()
{

    int bufferDrawn = 0;
    for (i = 0; i < BUFFER_LENGTH; i++)
    {
        //     // Get the tile index from the map
        if (buffer[i] > -1)
        {
            drawMapTile(buffer[i]);
            buffer[i] = -1;
            bufferDrawn = 1;
        }
    }
    if (bufferDrawn)
    {
        blitMapToVideoRam();
    }
}

// Function to draw the score
void drawScore()
{

    // Calculate the x position of the score string
    // int x = (320 - (strlen(scoreString) * 8)) / 2;

    // Draw the score string
    drawText(sprintScoreString(score), 0, 2);
}

// Function to show the game over screen
void gameOverScreen()
{
    // // Clear the map
    // for (int x = 0; x < mapWidth; x++)
    // {
    //     for (int y = 0; y < mapHeight; y++)
    //     {
    //         map[x][y] = 0;
    //     }
    // }

    // // Convert the score to a string
    // char scoreString[16];
    // sprintf(scoreString, "SCORE: %d", score);

    // // Calculate the x position of the score string
    // int x = (320 - (strlen(scoreString) * 8)) / 2;

    // // Draw the game over
    // // Draw the game over text
    // VDP_drawText("GAME OVER", 15, 13);
    // VDP_drawText(scoreString, 1, 92);

    // // Wait for button press
    // while (1)
    // {
    //     VDP_waitVSync();
    //     SYS_doVBlankProcess();
    //     u16 buttons = JOY_readJoypad(JOY_1);
    //     if (buttons & BUTTON_A)
    //     {
    //         break;
    //     }
    // }
}

int main()
{
    // Initialize the video system
    initScreen();

    // Initialize the snake
    snakeLength = SNAKE_START_LENGTH;
    snake[0].x = 1;
    snake[0].y = 1;
    snake[0].index = snake[0].y * mapWidth + snake[0].x;
    snake[0].xVelocity = 1;
    snake[0].yVelocity = 0;
    for (i = 1; i < snakeLength; i++)
    {
        snake[i].x = snake[i - 1].x - 1;
        snake[i].y = snake[i - 1].y;
        snake[i].index = snake[i].y * mapWidth + snake[i].x;
    }

    // Set the initial speed
    speed = SPEED_MIN;

    // Set the initial score
    score = 0;

    // Set the initial game over flag
    gameOver = 0;

    // Set the initial apple eaten flag
    appleEaten = 1;

    drawMap();

    // Main game loop
    while (!gameOver)
    {
        // Update the apple
        updateApple();

        // Update the snake
        updateSnake();

        // // Check if the snake ate the apple
        if (snake[0].index == appleIndex)
        {
            // Increment the score
            score++;

            // // Increment the snake length
            snakeLength++;

            // // Decrease the speed
            speed = SPEED_MIN + ((SPEED_MAX - SPEED_MIN) * (score / 20));

            // // Set the apple eaten flag
            appleEaten = 1;
            updateApple();
        }

        drawBuffer();
        drawScore();

        //doVSync();

        // Read the joypad
        u16 buttonInput = getInput();

        // Check for button presses
        if (buttonInput & inputUp)
        {
            if (snake[0].yVelocity != 1)
            {
                snake[0].xVelocity = 0;
                snake[0].yVelocity = -1;
            }
        }
        else if (buttonInput & inputDown)
        {
            if (snake[0].yVelocity != -1)
            {
                snake[0].xVelocity = 0;
                snake[0].yVelocity = 1;
            }
        }
        else if (buttonInput & inputLeft)
        {
            if (snake[0].xVelocity != 1)
            {
                snake[0].xVelocity = -1;
                snake[0].yVelocity = 0;
            }
        }
        else if (buttonInput & inputRight)
        {
            if (snake[0].xVelocity != -1)
            {
                snake[0].xVelocity = 1;
                snake[0].yVelocity = 0;
            }
        }
    }

    // Show the game over screen
    gameOverScreen();

    return 0;
}
