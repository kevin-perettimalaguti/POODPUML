#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game/vue/Grid.h"
#include "game/vue/Tile.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GRID_ROWS = 10;
const int GRID_COLS = 10;
const int CELL_SIZE = 50;
const int TILE_SELECTION_WIDTH = 150; // Increased width of the tile selection area

bool init(SDL_Window*& window, SDL_Renderer*& renderer);
void close(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!init(window, renderer)) {
        std::cerr << "Failed to initialize!\n";
        return -1;
    }

    Grid grid(GRID_ROWS, GRID_COLS, CELL_SIZE);
    std::vector<Tile> tiles;
    tiles.emplace_back("assets/place/Tiles/1.png", 1, renderer);
    tiles.emplace_back("assets/place/Tiles/2.png", 2, renderer);

    int selectedTileId = 1;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x < TILE_SELECTION_WIDTH) { // Tile selection area
                    int tileIndex = y / CELL_SIZE;
                    if (tileIndex >= 0 && tileIndex < tiles.size()) {
                        selectedTileId = tiles[tileIndex].getId();
                    }
                } else { // Grid area
                    int row = y / CELL_SIZE;
                    int col = (x - TILE_SELECTION_WIDTH) / CELL_SIZE;
                    grid.setTile(row, col, selectedTileId);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw the tile selection area
        for (size_t i = 0; i < tiles.size(); ++i) {
            tiles[i].draw(renderer, 0, i * CELL_SIZE);
        }

        // Draw the selected tile indicator
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red outline
        SDL_Rect selectedRect = {0, (selectedTileId - 1) * CELL_SIZE, TILE_SELECTION_WIDTH, CELL_SIZE};
        SDL_RenderDrawRect(renderer, &selectedRect);

        // Draw the grid
        grid.draw(renderer, TILE_SELECTION_WIDTH, 0); // Adjusted position of the grid

        SDL_RenderPresent(renderer);
    }

    grid.saveLevel("level.txt");
    close(window, renderer);
    return 0;
}

bool init(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow("SDL Tower Defense yes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    return true;
}

void close(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
