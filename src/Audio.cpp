#include "Audio.hpp"

Audio::Audio() : volume(MIX_MAX_VOLUME) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cerr << "Failed to initialize SDL_mixer! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

Audio::~Audio() {
    // Free music
    for (auto& pair : musicMap) {
        Mix_FreeMusic(pair.second);
    }
    musicMap.clear();
    
    // Free sound effects
    for (auto& pair : soundMap) {
        Mix_FreeChunk(pair.second);
    }
    soundMap.clear();
    
    Mix_CloseAudio();
}

void Audio::LoadMusic(const std::string& id, const std::string& filePath) {
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (music) {
        musicMap[id] = music;
    } else {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void Audio::LoadSound(const std::string& id, const std::string& filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (sound) {
        soundMap[id] = sound;
    } else {
        std::cerr << "Failed to load sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void Audio::PlayMusic(const std::string& id, int loops) {
    auto it = musicMap.find(id);
    if (it != musicMap.end()) {
        Mix_PlayMusic(it->second, loops);
    } else {
        std::cerr << "Music ID not found!" << std::endl;
    }
}

void Audio::PlaySound(const std::string& id, int loops) {
    auto it = soundMap.find(id);
    if (it != soundMap.end()) {
        Mix_PlayChannel(-1, it->second, loops);
    } else {
        std::cerr << "Sound ID not found!" << std::endl;
    }
}

void Audio::SetVolume(int volume) {
    this->volume = volume;
    Mix_Volume(-1, volume); // Set volume for all channels
    Mix_VolumeMusic(volume); // Set volume for music
}