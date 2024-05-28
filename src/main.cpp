#include "raylib.h"
#include "Grid.hpp"

int main() {
    int screenWidth = 800;
    int screenHeight = 600;
    int cellSize = 32;
    Grid grid(screenWidth / cellSize, screenHeight / cellSize, cellSize);

    InitWindow(screenWidth, screenHeight, "Raylib - Tower Defense Grid");

    // Load tiles from assets folder
    grid.loadTiles("assets/free-fields-tileset-pixel-art-for-tower-defense");

    // Load level from file if exists
    grid.loadFromFile("level.txt");

    SetTargetFPS(60);

    bool isDragging = false;
    Vector2 lastMousePos = {0, 0};

    while (!WindowShouldClose()) {
        grid.update();

        // Handle mouse input to set tile indices
        Vector2 mousePos = GetMousePosition();
        int x = static_cast<int>(mousePos.x) / cellSize;
        int y = static_cast<int>(mousePos.y) / cellSize;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isDragging = true;
            grid.setCell(x, y, 0);  // Set the first tile as an example
            lastMousePos = mousePos;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isDragging = false;
        }

        if (isDragging && (mousePos.x != lastMousePos.x || mousePos.y != lastMousePos.y)) {
            grid.setCell(x, y, 0);  // Set the first tile as an example
            lastMousePos = mousePos;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        grid.draw();
        EndDrawing();
    }

    // Save level to file before exiting
    grid.saveToFile("level.txt");

    CloseWindow();

    return 0;
}
