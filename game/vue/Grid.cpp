// Grid.cpp
#include "Grid.h"
#include <fstream>
#include <iostream>

Grid::Grid(int rows, int cols, int cellSize)
    : rows(rows), cols(cols), cellSize(cellSize), grid(rows, std::vector<int>(cols, 0)) {}

void Grid::draw(SDL_Renderer* renderer, int x, int y) { // Adjusted to accept position arguments
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            SDL_Rect rect = { x + j * cellSize, y + i * cellSize, cellSize, cellSize }; // Adjusted position
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderFillRect(renderer, &rect);

            if (grid[i][j] != 0) {
                // Draw the tile image
                // Assuming you have a texture manager or similar to handle textures
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