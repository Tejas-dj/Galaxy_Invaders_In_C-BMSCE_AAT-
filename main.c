#include <stdio.h>
#include <windows.h> 
#include "entities.h"
#include "renderer.h"
#include "logic.h"
#include "storage.h" 


void enableAnsi() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= 0x0004; 
    SetConsoleMode(hOut, dwMode);
}

void showStartScreen() {
    printf("\033[H\033[J");
    printf("\n\n\n");
    printf("     ================================\n");
    printf("       G A L A X Y   I N V A D E R S \n");
    printf("     ================================\n");
    printf("\n");
    printf("         [A] Move Left  [D] Move Right\n");
    printf("         [SPACE] Fire   [Q] Quit\n");
    printf("\n");
    printf("      PRESS [ENTER] TO START MISSION\n");
    
    getchar(); 
}




int main() 
{

    enableAnsi();

    // 1. Initialization
    int storedHighScore = loadHighScore(); 

    showStartScreen();

    Player p1 = { 
        .x = WIDTH / 2, 
        .y = HEIGHT - 2, 
        .symbol = '^', 
        .alive = 1, 
        .score = 0, 
        .hp = 3,
        .highScore = storedHighScore 
    };
    
    Alien enemies[MAX_ALIENS];
    for(int i = 0; i < MAX_ALIENS; i++) {
        enemies[i].x = 5 + (i * 6); 
        enemies[i].y = 2;
        enemies[i].symbol = 'M';
        enemies[i].active = 1;
        enemies[i].direction = 1; 
    }

    Bullet bullets[MAX_BULLETS];
    for(int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = 0;
        bullets[i].symbol = '|';
        bullets[i].dy = 0; 
    }

    // 2. The Game Loop
    int running = 1;
    int gameState = 0;

    while (running) {
        handleInput(&p1, bullets);

        gameState = updateGame(bullets, enemies, MAX_ALIENS, &p1);

        renderFrame(&p1, enemies, MAX_ALIENS, bullets);
        Sleep(33);

        // CHECK GAME OVER
        if (gameState != 0) {
            running = 0;
        }
    }

    renderFrame(&p1, enemies, MAX_ALIENS, bullets); 
    printf("\n\n");

    if (gameState == 1) {
        printf("=== MISSION ACCOMPLISHED ===\n");
    } else {
        printf("=== GAME OVER ===\n");
        printf("The aliens invaded Earth.\n");
    }
    
    printf("Final Score: %d\n", p1.score);

    if (p1.score > p1.highScore) {
        printf("\n*** NEW HIGH SCORE! ***\n");
        saveHighScore(p1.score); 
    } else {
        printf("\nHigh Score to Beat: %d\n", p1.highScore);
    }

    printf("\nPress Enter to exit...");
    getchar(); 
    getchar(); 

    return 0;
}