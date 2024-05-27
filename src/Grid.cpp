#include "Grid.hpp"
#include <filesystem>
#include <raylib.h>

Grid::Grid(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), cells(width, std::vector<int>(height, -1)) {}

Grid::~Grid() {
    unloadTiles();
}

void Grid::loadTiles(const std::string& folderPath) {
    unloadTiles();

    int index = 0;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            Texture2D texture = LoadTexture(filePath.c_str());
            tileTextures[index] = texture;
            index++;
        }
    }
}

void Grid::unloadTiles() {
    for (auto& tile : tileTextures) {
        UnloadTexture(tile.second);
    }
    tileTextures.clear();
}

void Grid::draw() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tileIndex = cells[x][y];
            if (tileIndex != -1 && tileTextures.find(tileIndex) != tileTextures.end()) {
                DrawTexture(tileTextures[tileIndex], x * cellSize, y * cellSize, WHITE);
            } else {
                DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, WHITE);
                DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, GRAY);
            }
        }
    }
}

void Grid::update() {
    // For future updates if needed
}

void Grid::setCell(int x, int y, int tileIndex) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[x][y] = tileIndex;
    }
}

int Grid::getCell(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return cells[x][y];
    }
    return -1;
}
