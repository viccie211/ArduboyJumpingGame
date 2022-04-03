#include "globals.h"
#include "levelReading.h"
#ifndef MOVEMENT_H
#define MOVEMENT_H

bool checkSolidTile(int16_t checkX, short checkY)
{
    int16_t fieldX = divideByTileSize(checkX);
    short fieldY = divideByTileSize(checkY);
    return readFromLevel(fieldX, fieldY) > 0;
}

short hittingVertical(int16_t x, short currentY, short targetedY)
{
    short returnValue = 0;
    if (currentY < targetedY)
    {
        // going down
        returnValue = targetedY;
        bool toBreak = false;
        for (int16_t y = currentY; y < targetedY && !toBreak; y++)
        {
            if (checkSolidTile(x, y + TILE_SIZE) || checkSolidTile(x + TILE_SIZE - 1, y + TILE_SIZE))
            {
                velocityY = 0;
                returnValue = y;
                toBreak = true;
            }
        }
    }
    else
    {
        // going up
        returnValue = targetedY;
        bool toBreak = false;
        for (int16_t y = currentY; y > targetedY && !toBreak; y--)
        {
            if (checkSolidTile(x, y - 1) || checkSolidTile(x + TILE_SIZE - 1, y - 1))
            {
                velocityY = 0;
                returnValue = y;
                toBreak = true;
            }
        }
    }
    return returnValue;
}

short hittingHorizontal(short y, int16_t currentX, int16_t targetedX)
{
    if (targetedX < 0)
    {
        return 0;
    }
    if (targetedX >= 508)
    {
        return 508;
    }
    int16_t returnValue = 0;
    if (currentX < targetedX)
    {
        // going right
        returnValue = targetedX;
        bool toBreak = false;
        for (int16_t x = currentX; x < targetedX && !toBreak; x++)
        {
            if (checkSolidTile(x + TILE_SIZE, y) || checkSolidTile(x + TILE_SIZE, y + TILE_SIZE - 1))
            {
                velocityX = 0;
                returnValue = x;
                toBreak = true;
            }
        }
    }
    else
    {
        // going left
        returnValue = targetedX;
        bool toBreak = false;
        for (int16_t x = currentX; x > targetedX && !toBreak; x--)
        {
            if (checkSolidTile(x - 1, y) || checkSolidTile(x - 1, y + TILE_SIZE - 1))
            {
                velocityX = 0;
                returnValue = x;
                toBreak = true;
            }
        }
    }
    return returnValue;
}
void calculateVelocityX()
{
    if (arduboy.pressed(RIGHT_BUTTON) || arduboy.pressed(LEFT_BUTTON))
    {
        if (arduboy.pressed(RIGHT_BUTTON))
        {
            if (velocityX < MAX_X_SPEED)
            {
                velocityX++;
            }
        }
        if (arduboy.pressed(LEFT_BUTTON))
        {
            if (velocityX > -MAX_X_SPEED)
            {
                velocityX--;
            }
        }
    }
    else
    {
        if (slowdown && velocityX != 0)
        {
            if (velocityX > 0)
            {
                velocityX--;
            }
            else if (velocityX < 0)
            {
                velocityX++;
            }
            slowdown = false;
        }
        else
        {
            slowdown = true;
        }
    }
}


void calculateVelocityY()
{
    bool checkedcheckSolidTile = checkSolidTile(playerX, playerY + TILE_SIZE) || checkSolidTile(playerX + TILE_SIZE - 1, playerY + TILE_SIZE);
    if (checkedcheckSolidTile && arduboy.pressed(A_BUTTON))
    {
        velocityY += JUMP_SPEED;
    }
    else if (checkedcheckSolidTile && velocityY > 0)
    {
        velocityY = 0;
    }
    if (!checkedcheckSolidTile)
    {
        velocityY += 1;
    }
}


void moveIfPossible()
{
    int16_t targetedX = playerX + velocityX;
    playerX = hittingHorizontal(playerY, playerX, targetedX);

    short targetedY = playerY + velocityY;
    playerY = hittingVertical(playerX, playerY, targetedY);
}

void move()
{
    calculateVelocityX();
    calculateVelocityY();
    moveIfPossible();
}
#endif