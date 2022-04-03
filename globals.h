#include <Arduboy2.h>
#ifndef GLOBALS_H
#define GLOBALS_H
#define TILE_SIZE 4
#define FIELD_HEIGHT HEIGHT / TILE_SIZE
#define FIELD_WIDTH 128
#define TITLE_SCREEN 0
#define LEVEL_SPLASH 1
#define GAME_PLAY 2
#define GAME_OVER 3
#define MAX_X_SPEED 3
#define JUMP_SPEED -6
#define FRAMERATE 30
#define ANIM_IDLE 0
#define ANIM_RIGHT 2
#define ANIM_LEFT 1
#define ANIM_UP 3
#define ANIM_DOWN 4
#define MAX_FRAMES_LEVEL_SPLASH 100

Arduboy2 arduboy;

short gamestate = TITLE_SCREEN;
short velocityX = 0;
short velocityY = 0;
int16_t playerX = 30;
short playerY = 56;
int16_t scrollX = 0;
bool slowdown = true;
const float tileSizeMultiplier = 0.25f;
short framesLevelSplash = 0;
String levelNames[] = {"1-1"};
short currentLevel = 0;
const byte (*level)[16][32];
#endif