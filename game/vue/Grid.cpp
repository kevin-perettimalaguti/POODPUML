#include "Grid.h"
#include <fstream>
#include <iostream>
#include <SDL2/SDL_image.h>

Grid::Grid(int rows, int cols, int cellSize, SDL_Renderer* renderer)
    : rows(rows), cols(cols), cellSize(cellSize), grid(rows, std::vector<int>(cols, 0)) {}

Grid::~Grid() {
    for (auto texture : tileTextures) {
        SDL_DestroyTexture(texture);
    }
}

SDL_Texture* Grid::loadTexture(const std::string& path, SDL_Renderer* renderer) {
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

void Grid::loadTextures(SDL_Renderer* renderer, int numTextures) {
    for (int i = 1; i <= numTextures; ++i) {
        std::string path = "assets/place/Tiles/" + std::to_string(i) + ".png";
        SDL_Texture* texture = loadTexture(path, renderer);
        if (texture) {
            tileTextures.push_back(texture);
        }
    }
}

void Grid::draw(SDL_Renderer* renderer, int offsetX, int offsetY) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            SDL_Rect rect = { offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize };
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderFillRect(renderer, &rect);

            if (grid[i][j] != 0) {
                int textureIndex = grid[i][j] - 1;
                if (textureIndex >= 0 && textureIndex < tileTextures.size()) {
                    SDL_RenderCopy(renderer, tileTextures[textureIndex], nullptr, &rect);
                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void Grid::setTile(int row, int col, int tile) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        grid[row][col] = tile;
    }
}

int Grid::getTile(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return grid[row][col];
    }
    return -1;
}

bool Grid::isOccupied(int row, int col) const {
    return getTile(row, col) != 0;
}

const std::vector<std::vector<int>>& Grid::getGrid() const {
    return grid;
}

void Grid::saveLevel(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& row : grid) {
            for (const auto& tile : row) {
                file << tile << " ";
            }
            file << "\n";
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for saving: " << filename << "\n";
    }
}

void Grid::loadLevel(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        for (auto& row : grid) {
            for (auto& tile : row) {
                file >> tile;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for loading: " << filename << "\n";
    }
}
