#include "Enemy.h"

Enemy::Enemy(int x, int y, int size, int speed)
    : x(x), y(y), size(size), speed(speed) {}

void Enemy::update() {
    x += speed; // Move to the right
}

void Enemy::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for enemies
    SDL_Rect fillRect = { x, y, size, size };
    SDL_RenderFillRect(renderer, &fillRect);
}
