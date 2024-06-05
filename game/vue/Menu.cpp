#include "Menu.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>

Menu::Menu(SDL_Renderer* renderer, int width, int height)
    : renderer(renderer), selectedOption(0), width(width), height(height) {
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init: " << TTF_GetError() << "\n";
        exit(1);
    }
}

void Menu::addOption(const std::string& option) {
    options.push_back(option);
}

void Menu::draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    TTF_Font* font = TTF_OpenFont("assets/fonts/minecraft_font.ttf", 24);
    if (!font) {
        std::cerr << "TTF_OpenFont: " << TTF_GetError() << "\n";
        exit(1);
    }

    SDL_Color color = { 255, 255, 255, 255 };

    for (size_t i = 0; i < options.size(); ++i) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, options[i].c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        int textWidth = surface->w;
        int textHeight = surface->h;
        SDL_FreeSurface(surface);

        SDL_Rect dstRect = { (width - textWidth) / 2, (int)((height / 2) + i * 30), textWidth, textHeight };
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
        SDL_DestroyTexture(texture);
    }

    TTF_CloseFont(font);
    SDL_RenderPresent(renderer);
}

int Menu::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return -1;
        }
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    selectedOption = (selectedOption > 0) ? selectedOption - 1 : options.size() - 1;
                    break;
                case SDLK_DOWN:
                    selectedOption = (selectedOption < options.size() - 1) ? selectedOption + 1 : 0;
                    break;
                case SDLK_RETURN:
                    return selectedOption;
            }
        }
    }
    return -1;
}
