#include "RenderingWindow.hpp"
#include <iostream>

RenderingWindow::RenderingWindow()
    : gWindow(NULL), gRenderer(NULL) {}

RenderingWindow::~RenderingWindow() {
    close();
}

bool RenderingWindow::initialize(const std::string& title, int pwidth, int pheight) {
    height = pheight;
    width = pwidth;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

   gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return true;
}

void RenderingWindow::close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    TTF_Quit();
    SDL_Quit();
}

SDL_Renderer* RenderingWindow::getRenderer() const {
    return gRenderer;
}

int RenderingWindow::getHeight()
{
    return height;
}

int RenderingWindow::getWidth()
{
    return width;
}

SDL_Window* RenderingWindow::getWindow() const {
    return gWindow;
}