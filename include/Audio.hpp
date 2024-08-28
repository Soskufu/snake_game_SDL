#pragma once
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <iostream>
#include <string>

class Audio {
public:
    Audio();
    ~Audio();
    
    void LoadMusic(const std::string& id, const std::string& filePath);
    void LoadSound(const std::string& id, const std::string& filePath);
    
    void PlayMusic(const std::string& id, int loops = -1);
    void PlaySound(const std::string& id, int loops = 0);
    
    void SetVolume(int volume);
    
private:
    std::unordered_map<std::string, Mix_Music*> musicMap;
    std::unordered_map<std::string, Mix_Chunk*> soundMap;
    int volume;
};