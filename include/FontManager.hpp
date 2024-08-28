#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

class FontManager {
public:
    // Constructor takes a pointer to SDL_Renderer
    FontManager(SDL_Renderer* renderer);

    // Destructor cleans up loaded fonts and text textures
    ~FontManager();

    // Load a font from file and store it with an ID
    void LoadFont(const std::string& id, const std::string& filePath, int size);

    // Get a font by its ID
    TTF_Font* GetFont(const std::string& id) const;

    // Render text to the screen
    void RenderText(const std::string& fontID, const std::string& text, SDL_Color color, int x, int y);

    // Clear all loaded fonts and text textures
    void Clear();

private:
    // Create a texture from text and store it
    void CreateTextTexture(const std::string& fontID, const std::string& text, SDL_Color color);

    // Map of font ID to TTF_Font pointers
    std::unordered_map<std::string, TTF_Font*> fonts;

    // Map of text to SDL_Texture pointers (cached text textures)
    std::unordered_map<std::string, SDL_Texture*> textTextures;

    // Pointer to the SDL_Renderer
    SDL_Renderer* renderer;
};