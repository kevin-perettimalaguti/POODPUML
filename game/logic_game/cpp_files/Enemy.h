#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <vector>

class Enemy {
public:
    Enemy(int x, int y, int size, int speed);
    void update(const std::vector<std::vector<int>>& grid, float deltaTime);
    void draw(SDL_Renderer* renderer) const;

private:
    int x;
    int y;
    int size;
    int speed;
    float elapsed; // To keep track of the accumulated time
    std::vector<std::pair<int, int>> path; // Path for the enemy
    size_t pathIndex; // Current index in the path
    void findPath(const std::vector<std::vector<int>>& grid);
};

#endif // ENEMY_H
