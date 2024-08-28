#include "FontManager.hpp"
#include <iostream>

FontManager::FontManager(SDL_Renderer* renderer)
    : renderer(renderer) {}

FontManager::~FontManager() {
    Clear();
}

void FontManager::LoadFont(const std::string& id, const std::string& filePath, int size) {
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), size);
    if (font) {
        fonts[id] = font;
    } else {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
    }
}

TTF_Font* FontManager::GetFont(const std::string& id) const {
    auto it = fonts.find(id);
    return it != fonts.end() ? it->second : nullptr;
}

void FontManager::Clear() {
    for (auto& pair : fonts) {
        TTF_CloseFont(pair.second);
    }
    fonts.clear();
    
    // Also clear any cached text textures
    for (auto& pair : textTextures) {
        SDL_DestroyTexture(pair.second);
    }
    textTextures.clear();
}

void FontManager::RenderText(const std::string& fontID, const std::string& text, SDL_Color color, int x, int y) {
    auto it = textTextures.find(text);
    if (it == textTextures.end()) {
        CreateTextTexture(fontID, text, color);
        it = textTextures.find(text);
    }

    if (it != textTextures.end()) {
        SDL_Rect destRect = { x, y, 0, 0 };
        SDL_QueryTexture(it->second, NULL, NULL, &destRect.w, &destRect.h);
        SDL_RenderCopy(renderer, it->second, NULL, &destRect);
    } else {
        std::cerr << "Text texture not found!" << std::endl;
    }
}

void FontManager::CreateTextTexture(const std::string& fontID, const std::string& text, SDL_Color color) {
    TTF_Font* font = GetFont(fontID);
    if (!font) {
        std::cerr << "Font not found!" << std::endl;
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface) {
        std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture) {
        std::cerr << "Unable to create texture from text surface! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    textTextures[text] = textTexture;
}
