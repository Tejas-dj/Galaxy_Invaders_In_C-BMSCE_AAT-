#include <conio.h> 
#include <stdlib.h> 
#include "logic.h"

void handleInput(Player *p, Bullet bullets[]) {
    if (_kbhit()) {
        char key = _getch();

        if (key == 'a' && p->x > 1) p->x--;
        if (key == 'd' && p->x < WIDTH - 2) p->x++;

        if (key == ' ') {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) { 
                    bullets[i].active = 1;
                    bullets[i].x = p->x;
                    bullets[i].y = p->y - 1;
                    bullets[i].dy = -1; // 
                    bullets[i].symbol = '|';
                    break; 
                }
            }
        }
    }
}

int updateGame(Bullet bullets[], Alien aliens[], int alienCount, Player *p) {
    
    // 1. UPDATE BULLETS
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y += bullets[i].dy; 
            
            if (bullets[i].y < 0 || bullets[i].y >= HEIGHT) {
                bullets[i].active = 0;
            }
        }
    }

    // 2. UPDATE ALIENS (Movement + Shooting)
    int activeAliens = 0;
    for (int i = 0; i < alienCount; i++) {
        if (!aliens[i].active) continue;

        activeAliens++;

        // A. Movement
        aliens[i].x += aliens[i].direction;
        if (aliens[i].x >= WIDTH - 2 || aliens[i].x <= 1) {
            aliens[i].direction *= -1;
            aliens[i].y++;
            
            if (aliens[i].y >= p->y) {
                return -1; 
            }
        }

        // B. SHOOTING LOGIC
        if (rand() % 50 == 0) {
            for (int b = 0; b < MAX_BULLETS; b++) {
                if (!bullets[b].active) {
                    bullets[b].active = 1;
                    bullets[b].x = aliens[i].x;
                    bullets[b].y = aliens[i].y + 1;
                    bullets[b].dy = 1;
                    bullets[b].symbol = '*';
                    break;
                }
            }
        }
    }

    // WIN CHECK
    if (activeAliens == 0) {
        return 1; // VICTORY
    }

    // 3. COLLISION DETECTION
    for (int b = 0; b < MAX_BULLETS; b++) {
        if (!bullets[b].active) continue;

        // CASE A:Enemy Attack
        if (bullets[b].dy == 1) {
            if (bullets[b].x == p->x && bullets[b].y == p->y) {
                bullets[b].active = 0; 
                p->hp--;               
                if (p->hp <= 0) return -1; 
            }
        }
        
        // CASE B: Player Attack
        else if (bullets[b].dy == -1) {
            for (int a = 0; a < alienCount; a++) {
                if (!aliens[a].active) continue;

                if (aliens[a].x == bullets[b].x && aliens[a].y == bullets[b].y) {
                    aliens[a].active = 0;  
                    bullets[b].active = 0; 
                    p->score += 100; 
                }
            }
        }
    }

    return 0; 
}