#ifndef LOGIC_H
#define LOGIC_H

#include "entities.h"

//Keyboard input
void handleInput(Player *p, Bullet bullets[]);

int updateGame(Bullet bullets[], Alien aliens[], int alienCount, Player *p);

#endif