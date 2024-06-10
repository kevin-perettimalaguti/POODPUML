#include "Enemy.h"
#include <cmath>
#include <iostream>
#include <queue>
#include <utility>

Enemy::Enemy(int x, int y, int size, int speed)
    : x(x), y(y), size(size), speed(speed), elapsed(0.0f), pathIndex(0) {
    std::cout << "Enemy created at (" << x << ", " << y << ") with size " << size << " and speed " << speed << std::endl;
}

void Enemy::findPath(const std::vector<std::vector<int>>& grid) {
    // Clear any previous path
    path.clear();

    // Simple BFS for pathfinding
    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::queue<std::pair<int, int>> q;
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    q.push({y / size, x / size});
    visited[y / size][x / size] = true;

    while (!q.empty()) {
        auto [curRow, curCol] = q.front();
        q.pop();

        for (auto [dr, dc] : directions) {
            int newRow = curRow + dr;
            int newCol = curCol + dc;

            // Check if the new position is valid and not visited
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow][newCol] && grid[newRow][newCol] == 0) {
                q.push({newRow, newCol});
                visited[newRow][newCol] = true;

                // Record the path
                path.push_back({newCol * size, newRow * size});
                
                // Stop if we reach the top row
                if (newRow == 0) {
                    return;
                }
            }
        }
    }
}

void Enemy::update(const std::vector<std::vector<int>>& grid, float deltaTime) {
    elapsed += deltaTime;
    if (elapsed >= 0.5f) { // Adjust this for speed control
        if (pathIndex >= path.size()) {
            findPath(grid); // Find a new path if the current one is finished
            pathIndex = 0;
        }
        if (pathIndex < path.size()) {
            y = path[pathIndex].second;
            x = path[pathIndex].first;
            pathIndex++;
        }
        elapsed = 0.0f;
        std::cout << "Enemy updated to (" << x << ", " << y << ")" << std::endl;
    }
}

void Enemy::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for enemies

    for (int w = 0; w < size * 2; w++) {
        for (int h = 0; h < size * 2; h++) {
            int dx = size - w; // horizontal offset
            int dy = size - h; // vertical offset
            if ((dx*dx + dy*dy) <= (size * size)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }

    std::cout << "Enemy drawn at (" << x << ", " << y << ") with size " << size << std::endl;
}
