#include <stdio.h>
#include <string.h>
#include <windows.h> 
#include "renderer.h"

// --- CURSOR LOGIC ---
void setCursorPosition(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void clearScreen() {
    setCursorPosition(0, 0); 
}

void renderFrame(Player *p, Alien aliens[], int alienCount, Bullet bullets[]) {
    char screen[HEIGHT][WIDTH];

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = ' ';
        }
    }

    // Player
    if (p->alive && p->x >= 0 && p->x < WIDTH && p->y >= 0 && p->y < HEIGHT) {
        screen[p->y][p->x] = p->symbol;
    }
    // Aliens
    for (int i = 0; i < alienCount; i++) {
        if (aliens[i].active) {
            if (aliens[i].x >= 0 && aliens[i].x < WIDTH && aliens[i].y >= 0 && aliens[i].y < HEIGHT)
                screen[aliens[i].y][aliens[i].x] = aliens[i].symbol;
        }
    }
    // Bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            if (bullets[i].x >= 0 && bullets[i].x < WIDTH && bullets[i].y >= 0 && bullets[i].y < HEIGHT)
                screen[bullets[i].y][bullets[i].x] = bullets[i].symbol;
        }
    }

    clearScreen();
    
    // UI Header (Yellow)
    printf("%sSCORE: %d  |  HI-SCORE: %d  |  LIVES: %d%s\n", 
            COLOR_YELLOW, p->score, p->highScore, p->hp, COLOR_RESET);
    
    // Top Border (White)
    printf(COLOR_WHITE);
    for(int i=0; i<WIDTH+2; i++) printf("#");
    printf("\n");

    // Main Grid
    for (int y = 0; y < HEIGHT; y++) {
        printf("#"); // Left border
        for (int x = 0; x < WIDTH; x++) {
            char pixel = screen[y][x];
            
            // COLOR LOGIC
            if (pixel == '^') {
                printf("%s%c%s", COLOR_CYAN, pixel, COLOR_WHITE); // Player = Cyan
            } 
            else if (pixel == 'M') {
                printf("%s%c%s", COLOR_GREEN, pixel, COLOR_WHITE); // Alien = Green
            } 
            else if (pixel == '|' || pixel == '*') {
                printf("%s%c%s", COLOR_RED, pixel, COLOR_WHITE); // Bullets = Red
            } 
            else {
                printf("%c", pixel); // Empty space
            }
        }
        printf("#\n"); // Right border
    }

    // Bottom Border
    for(int i=0; i<WIDTH+2; i++) printf("#");
    printf("%s\n", COLOR_RESET);
}