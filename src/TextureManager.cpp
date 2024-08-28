#include "TextureManager.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

bool TextureManager::LoadTexture(const std::string& key, const std::string& filePath, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return false;
    }

    textures[key] = texture;
    return true;
}

SDL_Texture* TextureManager::GetTexture(const std::string& key) const {
    auto it = textures.find(key);
    if (it != textures.end()) {
        return it->second;
    }
    return NULL;
}

void TextureManager::FreeTextures() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}

TextureManager::~TextureManager() {
    FreeTextures();
}