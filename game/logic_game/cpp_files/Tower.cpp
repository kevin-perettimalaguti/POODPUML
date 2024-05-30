#include "Tower.h"

Tower::Tower(int x, int y, int size)
    : x(x), y(y), size(size) {}

void Tower::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color for towers
    SDL_Rect fillRect = { x, y, size, size };
    SDL_RenderFillRect(renderer, &fillRect);
}
