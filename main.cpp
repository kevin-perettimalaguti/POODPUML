#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game/vue/Grid.h"
#include "game/vue/Menu.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GRID_ROWS = 10;
const int GRID_COLS = 10;
const int CELL_SIZE = 50;

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
    menu.addOption("Quit");

    bool inMenu = true;
    while (inMenu) {
        menu.draw();
        int option = menu.handleEvents();
        if (option == 0) {
            inMenu = false; // Start game
        } else if (option == 1) {
            close(window, renderer);
            return 0; // Quit
        }
    }

    Grid grid(GRID_ROWS, GRID_COLS, CELL_SIZE, renderer);

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
                int row = y / CELL_SIZE;
                int col = x / CELL_SIZE;
                if (row >= 0 && row < GRID_ROWS && col >= 0 && col < GRID_COLS && !grid.isOccupied(row, col)) {
                    grid.setTile(row, col, 1); // Place a tower (represented by tile value 1)
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw the grid
        grid.draw(renderer, 0, 0);

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

    int imgFlags = IMG_INIT_PNG;
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
