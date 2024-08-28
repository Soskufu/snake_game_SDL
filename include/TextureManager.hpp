#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

class TextureManager {
public:
    // Loads a texture from a file and associates it with a key
    bool LoadTexture(const std::string& key, const std::string& filePath, SDL_Renderer* renderer);
    
    // Retrieves a texture by its key
    SDL_Texture* GetTexture(const std::string& key) const;
    
    // Frees all loaded textures
    void FreeTextures();

    // Destructor to ensure proper cleanup
    ~TextureManager();

private:
    std::unordered_map<std::string, SDL_Texture*> textures; // Map to store textures by key
};