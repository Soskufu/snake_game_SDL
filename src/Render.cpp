#include "Render.hpp"

Render::Render(SDL_Renderer* renderer)
:renderer(renderer) {}

Render::~Render() {}

void Render::Clear() {
    SDL_RenderClear(renderer);
}

void Render::Present(SDL_Renderer* renderer) {
    SDL_RenderPresent(renderer);
}

void Render::DrawTexture(SDL_Renderer* renderer,SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect destRect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}
void Render::DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dst){
    SDL_RenderCopy(renderer, texture, NULL, dst);
}
void Render::DrawTexture(SDL_Renderer* renderer,SDL_Texture* texture)
{
    SDL_RenderCopy(renderer,texture, NULL, NULL);
}
void Render::DrawColor(SDL_Renderer* renderer,Uint8 red,Uint8 green,Uint8 blue,Uint8 alpha)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}