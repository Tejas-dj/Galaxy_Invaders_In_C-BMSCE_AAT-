#include <stdio.h>
#include "storage.h"

void saveHighScore(int score) {
    FILE *file = fopen("highscore.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", score);
        fclose(file);
    }
}

int loadHighScore() {
    int score = 0;
    FILE *file = fopen("highscore.txt", "r"); 
    if (file != NULL) {
        fscanf(file, "%d", &score);
        fclose(file);
    }
    return score;
}