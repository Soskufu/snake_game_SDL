#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Render {
public:
    Render(SDL_Renderer* renderer);
    ~Render();

    void Clear();
    void Present(SDL_Renderer* renderer);
    void DrawTexture(SDL_Renderer* renderer,SDL_Texture* texture, int x, int y, int w, int h);
    void DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dst);
    void DrawTexture(SDL_Renderer* renderer,SDL_Texture* texture);
    void DrawColor(SDL_Renderer* renderer,Uint8 red,Uint8 green,Uint8 blue,Uint8 alpha);

private:
    SDL_Renderer* renderer;
};