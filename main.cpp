#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game/vue/Grid.h"
#include "game/vue/Menu.h"
#include "game/logic_game/cpp_files/Enemy.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GRID_ROWS = 10;
const int GRID_COLS = 10;
const int CELL_SIZE = 50;
const int NUM_TILES = 5; // Number of tile textures available

bool init(SDL_Window*& window, SDL_Renderer*& renderer);
void close(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!init(window, renderer)) {
        std::cerr << "Failed to initialize!\n";
        return -1;
    }

    // Create and display the menu
    Menu menu(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    menu.addOption("Start Game");
    menu.addOption("Load Game");
    menu.addOption("Quit");

    bool inMenu = true;
    bool loadGame = false;
    bool loadSave = false;
    while (inMenu) {
        menu.draw();
        int option = menu.handleEvents(loadSave);
        if (option == 0) {
            inMenu = false; // Start game
        } else if (option == 1) {
            loadGame = true;
            inMenu = false; // Load game
        } else if (option == 2) {
            close(window, renderer);
            return 0; // Quit
        } else if (loadSave) {
            loadGame = true;
            inMenu = false;
        }
    }

    Grid grid(GRID_ROWS, GRID_COLS, CELL_SIZE, renderer);
    grid.loadTextures(renderer, NUM_TILES);
    grid.loadTowerTexture(renderer);

    if (loadGame) {
        grid.loadLevel("savefile.txt");
    }

    int currentTileIndex = 0;
    bool quit = false;
    SDL_Event e;

    std::vector<Enemy> enemies;
    Uint32 lastSpawnTime = SDL_GetTicks();

    Uint32 lastClickTime = 0;
    int lastRow = -1, lastCol = -1;

    while (!quit) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastSpawnTime) / 1000.0f;
        lastSpawnTime = currentTime;

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                int row = y / CELL_SIZE;
                int col = x / CELL_SIZE;

                if (row >= 0 && row < GRID_ROWS && col >= 0 && col < GRID_COLS) {
                    Uint32 clickTime = SDL_GetTicks();
                    if (clickTime - lastClickTime < 500 && row == lastRow && col == lastCol) {
                        grid.setTile(row, col, -1); // Place a tower (represented by tile value -1)
                    } else {
                        lastClickTime = clickTime;
                        lastRow = row;
                        lastCol = col;

                        if (!grid.isOccupied(row, col)) {
                            grid.setTile(row, col, currentTileIndex + 1); // Place a tile
                        }
                    }
                }
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_y) {
                    currentTileIndex = (currentTileIndex + 1) % NUM_TILES; // Cycle through the tile textures
                }
                if (e.key.keysym.sym == SDLK_s) {
                    grid.saveLevel("savefile.txt"); // Save the current level
                }
                if (e.key.keysym.sym == SDLK_f) {
                    grid.loadLevel("savefile.txt"); // Load the saved level
                }
            }
        }

        // Spawn enemies at intervals
        if (currentTime - lastSpawnTime > 1000) { // 1 second interval
            enemies.push_back(Enemy(rand() % (SCREEN_WIDTH - CELL_SIZE), SCREEN_HEIGHT - CELL_SIZE, CELL_SIZE, 100, renderer));
            lastSpawnTime = currentTime;
        }

        // Update enemies
        for (auto& enemy : enemies) {
            enemy.update(deltaTime);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw the grid
        grid.draw(renderer, 0, 0);

        // Draw enemies
        for (const auto& enemy : enemies) {
            enemy.draw(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    close(window, renderer);
    return 0;
}

bool init(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow("SDL Tower Defense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_AVIF;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    return true;
}

void close(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
