#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Menu {
public:
    Menu(SDL_Renderer* renderer, int width, int height);
    void addOption(const std::string& option);
    void draw();
    int handleEvents();

private:
    SDL_Renderer* renderer;
    std::vector<std::string> options;
    int selectedOption;
    int width;
    int height;
};

#endif // MENU_H
