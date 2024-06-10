#include "Menu.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Menu::Menu(SDL_Renderer* renderer, int width, int height)
    : renderer(renderer), selectedOption(0), width(width), height(height), backgroundTexture(nullptr), logoTexture(nullptr) {
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init: " << TTF_GetError() << "\n";
        exit(1);
    }

    backgroundTexture = loadTexture("assets/main_menu.avif");
    logoTexture = loadTexture("assets/Logo.png");
}

Menu::~Menu() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(logoTexture);
}

SDL_Texture* Menu::loadTexture(const std::string& path) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << "\n";
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Menu::renderTexture(SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect renderQuad = { x, y, w, h };
   
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
}

void Menu::addOption(const std::string& option) {
    options.push_back(option);
}

void Menu::draw() {
    SDL_RenderClear(renderer);

    // Render background
    if (backgroundTexture) {
        renderTexture(backgroundTexture, 0, 0, width, height);
    }

    // Render logo
    if (logoTexture) {
        int logoWidth = 400;
        int logoHeight = 400;
        int x = (width - logoWidth) / 2;
        int y = height / 4 - logoHeight / 2;
        renderTexture(logoTexture, x, y, logoWidth, logoHeight);
    }

    TTF_Font* font = TTF_OpenFont("assets/fonts/minecraft_font.ttf", 24);
    if (!font) {
        std::cerr << "TTF_OpenFont: " << TTF_GetError() << "\n";
        exit(1);
    }

    SDL_Color color = { 255, 255, 255, 255 };
    int yOffset = height / 2;

    for (size_t i = 0; i < options.size(); ++i) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, options[i].c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        int textWidth = surface->w;
        int textHeight = surface->h;
        SDL_FreeSurface(surface);

        SDL_Rect dstRect = { (width - textWidth) / 2, yOffset + static_cast<int>(i) * 30, textWidth, textHeight };
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
