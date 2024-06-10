#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Menu {
public:
    Menu(SDL_Renderer* renderer, int width, int height);
    ~Menu();
    void addOption(const std::string& option);
    void draw();
    int handleEvents();

private:
    SDL_Renderer* renderer;
    int selectedOption;
    int width;
    int height;
    std::vector<std::string> options;
    SDL_Texture* backgroundTexture;
    SDL_Texture* logoTexture;

    SDL_Texture* loadTexture(const std::string& path);
    void renderTexture(SDL_Texture* texture, int x, int y, int w, int h);
};

#endif // MENU_H
