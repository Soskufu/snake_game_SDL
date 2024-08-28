#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class RenderingWindow {
public:
    RenderingWindow();
    ~RenderingWindow();

    bool initialize(const std::string& title, int pwidth, int pheight);
    void close();
    SDL_Renderer* getRenderer() const;
    SDL_Window* getWindow() const;
    int getWidth();
    int getHeight();

private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    int width = 900;
    int height = 900;
};