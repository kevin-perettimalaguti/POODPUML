// Tile.h

#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <string>

class Tile {
public:
    Tile(const std::string& filePath, int id, SDL_Renderer* renderer);
    ~Tile();
    void draw(SDL_Renderer* renderer, int x, int y) const;
    int getId() const;

private:
    int id;
    SDL_Texture* texture;
};

#endif // TILE_H
