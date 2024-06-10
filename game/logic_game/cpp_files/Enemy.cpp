#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int x, int y, int size, int speed)
    : x(x), y(y), size(size), speed(speed) {
    std::cout << "Enemy created at (" << x << ", " << y << ") with size " << size << " and speed " << speed << std::endl;
}

void Enemy::update(float deltaTime) {
    y -= speed * deltaTime; // Move up
    std::cout << "Enemy updated to (" << x << ", " << y << ")" << std::endl;
}

void Enemy::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for enemies
    SDL_Rect rect = { x, y, size, size };
    SDL_RenderFillRect(renderer, &rect);
}
