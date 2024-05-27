#include "raylib.h"
#include <vector>
#include <utility>
#include <iostream> 

// Function to draw the grid based on the state of cells
void DrawGrid(const std::vector<std::vector<int>>& cells, int cellSize) {
    for (int row = 0; row < cells.size(); row++) {
        for (int column = 0; column < cells[row].size(); column++) {
            Color color = cells[row][column] ? Color{0, 0, 0, 255} : Color{255, 255, 255, 255};
            DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
        }
    }
}

// Function to set the value of a cell in the grid
void SetCellValue(std::vector<std::vector<int>>& cells, int row, int column, int value) {
    if (row >= 0 && row < cells.size() && column >= 0 && column < cells[0].size()) {
        cells[row][column] = value;
    }
}

// Function to count the number of live neighbors around a cell
int CountLiveNeighbors(const std::vector<std::vector<int>>& cells, int row, int column) {
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> neighborOffsets = {
        {-1, 0}, {1, 0}, {0, -1}, {0 , 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (const auto& offset : neighborOffsets) {
        int neighborRow = (row + offset.first + cells.size()) % cells.size();
        int neighborColumn = (column + offset.second + cells[0].size()) % cells[0].size(); 
        liveNeighbors += cells[neighborRow][neighborColumn];
    }

    return liveNeighbors;
}

// Function to update the state of the cells based on the Game of Life rules
void Update(std::vector<std::vector<int>>& cells, std::vector<std::vector<int>>& tempCells) {
    for (int row = 0; row < cells.size(); row++) {
        for (int column = 0; column < cells[row].size(); column++) {
            int liveNeighbors = CountLiveNeighbors(cells, row, column);
            int cellValue = cells[row][column];

            if (cellValue == 1) {
                if (liveNeighbors > 3 || liveNeighbors < 2) {
                    tempCells[row][column] = 0;
                } else {
                    tempCells[row][column] = 1;
                }
            } else {
                if (liveNeighbors == 3) {
                    tempCells[row][column] = 1;
                } else {
                    tempCells[row][column] = 0;
                }
            }
        }
    }

    // Update the current grid with the new states from the temporary grid
    for (int row = 0; row < cells.size(); row++) {
        for (int column = 0; column < cells[row].size(); column++) {
            cells[row][column] = tempCells[row][column];
        }
    }
}

// Function to randomly populate the grid with live and dead cells
void FillRandom(std::vector<std::vector<int>>& cells) {
    for (int row = 0; row < cells.size(); row++) {
        for (int column = 0; column < cells[row].size(); column++) {
            int randomValue = GetRandomValue(0, 4);
            cells[row][column] = (randomValue == 4) ? 1 : 0;
        }
    }
}

void FirstPatern(std::vector<std::vector<int>>& cells){
    for (int row = 0; row < cells.size(); row++) {
        for (int column = 0; column < cells[row].size(); column++) {
            cells[row][column] = 0;
        }
    }
    cells[1][5] = 1;
    cells[2][5] = 1;
    cells[3][5] = 1;
    cells[4][5] = 1;
    cells[5][5] = 1;
    cells[6][5] = 1;
    cells[7][5] = 1;
    cells[8][5] = 1;
    cells[9][5] = 1;
    cells[10][5] = 1;
    cells[11][5] = 1;
    cells[12][5] = 1;
    cells[13][5] = 1;
    cells[14][5] = 1;
    cells[15][5] = 1;
    cells[16][5] = 1;
    cells[17][5] = 1;
    cells[18][5] = 1;
    cells[19][5] = 1;
    cells[20][5] = 1;
    cells[21][5] = 1;
    cells[22][5] = 1;
    cells[23][5] = 1;
    cells[24][5] = 1;
    cells[25][5] = 1;
    cells[26][5] = 1;
    cells[27][5] = 1;
    cells[28][5] = 1;
    cells[29][5] = 1;
    cells[30][5] = 1;
    cells[31][5] = 1;
    cells[32][5] = 1;
    cells[33][5] = 1;
    cells[34][5] = 1;
    cells[35][5] = 1;
    cells[36][5] = 1;
    cells[37][5] = 1;
    cells[38][5] = 1;
    cells[39][5] = 1;
    cells[40][5] = 1;
    cells[41][5] = 1;
}


void LoadPopulation(std::vector<std::vector<int>>& cells, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        for (int row = 0; row < cells.size(); row++) {
            for (int column = 0; column < cells[row].size(); column++) {
                fscanf(file, "%d", &cells[row][column]);
            }
        }
        fclose(file);
    } else {
        std::cerr << "Erreur dans le fichier de sauvegarde" << filename << std::endl;
    }
}

// Function to save the current population to a text file
void SavePopulation(const std::vector<std::vector<int>>& cells, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        for (int row = 0; row < cells.size(); row++) {
            for (int column = 0; column < cells[row].size(); column++) {
                fprintf(file, "%d ", cells[row][column]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
        std::cout << "La Population à bien été sauvegarder!" << std::endl;
    } else {
        std::cerr << "Erreur dans le fichier de sauvegarde" << filename << std::endl;
    }
}

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 780;
    const int cellSize = 10;  

    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(12); 

    std::vector<std::vector<int>> cells(screenHeight / cellSize, std::vector<int>(screenWidth / cellSize, 0));
    std::vector<std::vector<int>> tempCells(screenHeight / cellSize, std::vector<int>(screenWidth / cellSize, 0));

    FillRandom(cells);

    bool drawGrid = false; 

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) { 
            FillRandom(cells);
            drawGrid = true; 
        }

        if (IsKeyPressed(KEY_F)) { 
            drawGrid = true;
            FirstPatern(cells);
        }

        if (IsKeyPressed(KEY_S)) { 
            SavePopulation(cells, "population.txt");
        }

        if (IsKeyPressed(KEY_G)) { 
            LoadPopulation(cells, "population.txt");
            drawGrid = true;
        }

        Update(cells, tempCells);
        BeginDrawing();

        ClearBackground(BLACK);

        if (!drawGrid) {
            DrawText("Welcome to Game of Life", (screenWidth - MeasureText("Welcome to Game of Life", 50)) / 2, screenHeight / 2 -300, 50, WHITE);
            DrawText("Press ENTER to play", (screenWidth - MeasureText("Press ENTER to play", 35)) / 2, screenHeight / 2 - 180, 35, WHITE);
            DrawText("Press S to save population", (screenWidth - MeasureText("Press ENTER to play", 40)) / 2, screenHeight / 2 + 40, 30, WHITE);
            DrawText("Press F to first patern", (screenWidth - MeasureText("Press ENTER to play", 40)) / 2, screenHeight / 2 + 120, 30, WHITE);
            DrawText("Press G to load population", (screenWidth - MeasureText("Press ENTER to play", 40)) / 2, screenHeight / 2 + 200, 30, WHITE);
        }

        if (drawGrid) { 
            DrawGrid(cells, cellSize);
        }
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}