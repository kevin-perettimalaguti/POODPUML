#ifndef TOWER_H
#define TOWER_H

#include <SDL2/SDL.h>

class Tower {
public:
    Tower(int x, int y, int size);
    void draw(SDL_Renderer* renderer) const; // Mark draw as const

private:
    int x;
    int y;
    int size;
};

#endif // TOWER_H
