#include "globals.h"
#ifndef LEVELREADING_H
#define LEVELREADING_H
byte readTileBitsFromByte(byte toRead, short tilePosition)
{
    byte shifted = toRead << tilePosition * 2;
    shifted = shifted >> 6;
    return shifted;
}

byte readFromLevel(int16_t x, short y)
{
    int16_t xByte = x / 4;
    byte readByte = pgm_read_byte(&((*level))[y][xByte]);

    return readTileBitsFromByte(readByte, x % 4);
}


int16_t divideByTileSize(int16_t input)
{
    return (int16_t)(input * tileSizeMultiplier);
}

#endif