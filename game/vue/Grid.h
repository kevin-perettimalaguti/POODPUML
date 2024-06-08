#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Grid {
public:
    Grid(int rows, int cols, int cellSize);
    void draw(SDL_Renderer* renderer, int offsetX, int offsetY);
    void setTile(int row, int col, int tile);
    int getTile(int row, int col) const;
    void saveLevel(const std::string& filename) const;
    void loadLevel(const std::string& filename);
    bool isOccupied(int row, int col) const;
    const std::vector<std::vector<int>>& getGrid() const; // Add this method

private:
    int rows;
    int cols;
    int cellSize;
    std::vector<std::vector<int>> grid;
};

#endif // GRID_H
