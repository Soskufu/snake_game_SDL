#pragma once

#include "RenderingWindow.hpp"
#include "TextureManager.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "Render.hpp"
#include "Config.hpp"
#include "Snake.hpp"
#include "Menu.hpp"

enum class GameState {
    MENU,
    GAME,
    EXIT
};

class GameManager {
public:
    GameManager(RenderingWindow& renderwindow,
                TextureManager& textureManager,
                Audio& audio,
                Input& input,
                Render& render,
                Config& config,
                Snake& snake,
                Menu& menu);

    void Run();  // Main game loop

private:
    void Update(float deltaTime);
    void HandleEvents();
    void nRender();

    RenderingWindow& renderwindow;
    TextureManager& textureManager;
    Audio& audio;
    Input& input;
    Render& render;
    Config& config;
    Snake& snake;
    Menu& menu;

    GameState state;
    float moveCounter;
    int score;
    bool gameOver;
    bool quit;
};

