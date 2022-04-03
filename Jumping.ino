#include <Arduboy2.h>
#include "maps.h"
#include "anims.h"
#include "movement.h"

void setup()
{
    // put your setup code here, to run once:
    arduboy.begin();
    arduboy.setFrameRate(FRAMERATE);
    level = &OneDashOne;
}

void loop()
{
    arduboy.pollButtons();

    if (!arduboy.nextFrame())
    {
        return;
    }
    arduboy.clear();

    switch (gamestate)
    {
    case TITLE_SCREEN:
        titleScreen();
        break;
    case LEVEL_SPLASH:
        levelSplash();
        break;
    case GAME_PLAY:
        gameplay();
        break;
    case GAME_OVER:
        gameOver();
        break;
    }
    arduboy.display();
}

void titleScreen()
{
    arduboy.print("Jumping");
    if (arduboy.pressed(A_BUTTON))
    {
        arduboy.initRandomSeed();
        gamestate = GAME_PLAY;
    }
}

void levelSplash()
{
    arduboy.print(levelNames[currentLevel]);
    if (framesLevelSplash >= MAX_FRAMES_LEVEL_SPLASH)
    {
        gamestate = GAME_PLAY;
        framesLevelSplash = 0;
        return;
    }
    framesLevelSplash++;
}

void gameplay()
{
    move();
    scroll();
    draw(scrollX);
}

void scroll()
{
    if (velocityX > 0 && playerX >= 64 && playerX + scrollX > 64 && scrollX - velocityX > -385)
    {
        scrollX -= velocityX;
    }
    else if (velocityX < 0 && playerX >= 18 && playerX + scrollX < 18 && scrollX - velocityX <= 0)
    {
        scrollX -= velocityX;
    }
}

void draw(int16_t scroll)
{
    drawBackground(scroll);
    drawPlayer(scroll);
}

void drawBackground(int16_t scroll)
{
    for (short y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int16_t x = (0 - (divideByTileSize(scroll)) - 1); x < (divideByTileSize(WIDTH) + (divideByTileSize(-scroll)) + 1); x++)
        {
            arduboy.fillRect((int16_t)(x * TILE_SIZE + scrollX), y * TILE_SIZE, TILE_SIZE, TILE_SIZE, readFromLevel(x, y));
        }
    }
}

void drawPlayer(int16_t scroll)
{
    short frame = ANIM_IDLE;

    if (velocityY < 0)
    {
        frame = ANIM_UP;
    }
    else if (velocityY > 0)
    {
        frame = ANIM_DOWN;
    }
    else if (arduboy.pressed(RIGHT_BUTTON))
    {
        frame = ANIM_RIGHT;
    }
    else if (arduboy.pressed(LEFT_BUTTON))
    {
        frame = ANIM_LEFT;
    }

    Sprites::drawSelfMasked(playerX + scroll, playerY, blobAnim, frame);
}

void gameOver()
{
    arduboy.print("You lost");
    if (arduboy.justPressed(A_BUTTON))
    {
        gamestate = TITLE_SCREEN;
    }
}

