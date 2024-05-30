#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

class Enemy {
public:
    Enemy(int x, int y, int size, int speed);
    void update();
    void draw(SDL_Renderer* renderer) const; // Mark draw as const

private:
    int x;
    int y;
    int size;
    int speed;
};

#endif // ENEMY_H
