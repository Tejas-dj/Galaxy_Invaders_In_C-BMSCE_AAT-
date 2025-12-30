#ifndef RENDERER_H
#define RENDERER_H

#include "entities.h"

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

void clearScreen();

void renderFrame(Player *p, Alien aliens[], int alienCount, Bullet bullets[]);

#endif