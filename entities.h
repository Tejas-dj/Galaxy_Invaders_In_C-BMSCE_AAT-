#ifndef ENTITIES_H
#define ENTITIES_H

// Dimensions for "Video Memory"
#define WIDTH 40
#define HEIGHT 20

// The Player
typedef struct {
    int x;
    int y;
    char symbol;
    int alive;
    int score;
    int hp;
    int highScore;
} Player;


#define MAX_ALIENS 5
// The Enemy
typedef struct {
    int x;
    int y;
    char symbol;
    int active;
    int direction;
} Alien;



#define MAX_BULLETS 10
// The Projectile
typedef struct {
    int x, y, active;
    char symbol; 
    int dy;
} Bullet;

#endif