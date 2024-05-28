#pragma once

#include <vector>
#include <raylib.h>
#include <unordered_map>
#include <string>

class Grid {
public:
    Grid(int width, int height, int cellSize);
    ~Grid();
    void draw();
    void update();
    void setCell(int x, int y, int tileIndex);
    int getCell(int x, int y);
    void loadTiles(const std::string& folderPath);
    void saveToFile(const std::string& filePath);
    void loadFromFile(const std::string& filePath);

private:
    int width, height, cellSize;
    std::vector<std::vector<int>> cells;
    std::unordered_map<int, Texture2D> tileTextures;

    void unloadTiles();
};
