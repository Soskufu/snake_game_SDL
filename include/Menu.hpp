#pragma once
#include "RenderingWindow.hpp"
#include "Input.hpp"
#include "FontManager.hpp"
#include <iostream>
class Menu {
public:
    Menu(RenderingWindow& gRenderingWindow,Input& input,FontManager& fontmanager);
    ~Menu();

    void loadMedia();
    void handleEvents();
    void render();
    void close();
    bool GetQuit();
    bool GetStartGame();
    bool GetOpenOptions();
    void SetStartGame(bool set);
    void SetQuit(bool set);
    void LogSetStartGame();

private:
    RenderingWindow& gRenderingWindow;
    Input& input;
    FontManager& fontmanager;
    TTF_Font* gFont;
    SDL_Texture* gTextTexture;
    SDL_Texture* gHoverTextTexture;
    SDL_Texture* gOptionsTexture;
    SDL_Texture* gHoverOptionsTexture;
    SDL_Texture* gQuitTexture;
    SDL_Texture* gHoverQuitTexture;

    SDL_Rect gStartRect;
    SDL_Rect gOptionsRect;
    SDL_Rect gQuitRect;

    bool gMouseHoverStart;
    bool gMouseHoverOptions;
    bool gMouseHoverQuit;
    bool startGame;
    bool openOptions;
    bool quit;
};

