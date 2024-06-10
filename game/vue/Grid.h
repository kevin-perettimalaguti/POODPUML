#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Grid {
public:
    Grid(int rows, int cols, int cellSize, SDL_Renderer* renderer);
    ~Grid();
    void draw(SDL_Renderer* renderer, int offsetX, int offsetY);
    void setTile(int row, int col, int tile);
    int getTile(int row, int col) const;
    void saveLevel(const std::string& filename) const;
    void loadLevel(const std::string& filename);
    bool isOccupied(int row, int col) const;
    const std::vector<std::vector<int>>& getGrid() const;
    void loadTextures(SDL_Renderer* renderer, int numTextures);
    void loadTowerTexture(SDL_Renderer* renderer);

private:
    int rows;
    int cols;
    int cellSize;
    std::vector<std::vector<int>> grid;
    std::vector<SDL_Texture*> tileTextures;
    SDL_Texture* towerTexture;
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
};

#endif // GRID_H
