// Tile.cpp

#include "Tile.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Tile::Tile(const std::string& filePath, int id, SDL_Renderer* renderer)
    : id(id), texture(nullptr) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Unable to load image " << filePath << "! SDL_image Error: " << IMG_GetError() << "\n";
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!texture) {
            std::cerr << "Unable to create texture from " << filePath << "! SDL Error: " << SDL_GetError() << "\n";
        }
    }
}

Tile::~Tile() {
    SDL_DestroyTexture(texture);
}

void Tile::draw(SDL_Renderer* renderer, int x, int y) const {
    SDL_Rect rect = { x, y, 50, 50 }; // Assuming a fixed tile size of 50x50
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

int Tile::getId() const {
    return id;
}
