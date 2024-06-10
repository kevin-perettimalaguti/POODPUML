#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <string>

class Enemy {
public:
    Enemy(int x, int y, int size, int speed, SDL_Renderer* renderer);
    ~Enemy();
    void update(float deltaTime);
    void draw(SDL_Renderer* renderer) const;

private:
    int x;
    int y;
    int size;
    int speed;
    SDL_Texture* texture;

    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
};

#endif // ENEMY_H
