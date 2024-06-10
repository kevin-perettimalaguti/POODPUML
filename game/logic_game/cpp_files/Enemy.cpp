#include "Enemy.h"
#include <iostream>
#include <SDL2/SDL_image.h>

Enemy::Enemy(int x, int y, int size, int speed, SDL_Renderer* renderer)
    : x(x), y(y), size(size), speed(speed), texture(nullptr) {
    texture = loadTexture("assets/archer/idle/1.png", renderer);
    if (texture == nullptr) {
        std::cerr << "Failed to load enemy texture!\n";
    }
}

Enemy::~Enemy() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* Enemy::loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << "\n";
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Enemy::update(float deltaTime) {
    y -= speed * deltaTime; // Move up
}

void Enemy::draw(SDL_Renderer* renderer) const {
    SDL_Rect rect = { x, y, size, size };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
