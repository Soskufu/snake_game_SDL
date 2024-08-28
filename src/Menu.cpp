#include "Menu.hpp"
#include <iostream>

Menu::Menu(RenderingWindow& gRenderingWindow,Input& input,FontManager& fontmanager)
    : gRenderingWindow(gRenderingWindow), input(input), fontmanager(fontmanager), gFont(nullptr), gTextTexture(nullptr),
      gHoverTextTexture(nullptr), gOptionsTexture(nullptr), gHoverOptionsTexture(nullptr),
      gQuitTexture(nullptr), gHoverQuitTexture(nullptr),
      gMouseHoverStart(false), gMouseHoverOptions(false), gMouseHoverQuit(false) {}

Menu::~Menu() {
    close();
}

void Menu::loadMedia() {
    gFont = TTF_OpenFont("res/Fonts/GamePlayed-vYL7.ttf", 84);
    if (gFont == nullptr) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Color hoverTextColor = { 255, 0, 0, 255 };  // Red color for hover

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, "Start", textColor);
    if (textSurface == nullptr) {
        std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }
    gTextTexture = SDL_CreateTextureFromSurface(gRenderingWindow.getRenderer(), textSurface);
    if (gTextTexture == nullptr) {
        std::cerr << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(textSurface);

    SDL_Surface* hoverTextSurface = TTF_RenderText_Solid(gFont, "Start", hoverTextColor);
    if (hoverTextSurface == nullptr) {
        std::cerr << "Unable to render hover text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }
    gHoverTextTexture = SDL_CreateTextureFromSurface(gRenderingWindow.getRenderer(), hoverTextSurface);
    if (gHoverTextTexture == nullptr) {
        std::cerr << "Unable to create texture from hover rendered text! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(hoverTextSurface);

    SDL_Surface* optionsSurface = TTF_RenderText_Solid(gFont, "Options", textColor);
    if (optionsSurface == nullptr) {
        std::cerr << "Unable to render options surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }
    gOptionsTexture = SDL_CreateTextureFromSurface(gRenderingWindow.getRenderer(), optionsSurface);
    if (gOptionsTexture == nullptr) {
        std::cerr << "Unable to create texture from rendered options! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(optionsSurface);

    SDL_Surface* hoverOptionsSurface = TTF_RenderText_Solid(gFont, "Options", hoverTextColor);
    if (hoverOptionsSurface == nullptr) {
        std::cerr << "Unable to render hover options surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }
    gHoverOptionsTexture = SDL_CreateTextureFromSurface(gRenderingWindow.getRenderer(), hoverOptionsSurface);
    if (gHoverOptionsTexture == nullptr) {
        std::cerr << "Unable to create texture from hover rendered options! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(hoverOptionsSurface);

    SDL_Surface* quitSurface = TTF_RenderText_Solid(gFont, "Quit", textColor);
    if (quitSurface == nullptr) {
        std::cerr << "Unable to render quit surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }
    gQuitTexture = SDL_CreateTextureFromSurface(gRenderingWindow.getRenderer(), quitSurface);
    if (gQuitTexture == nullptr) {
        std::cerr << "Unable to create texture from rendered quit! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(quitSurface);

    SDL_Surface* hoverQuitSurface = TTF_RenderText_Solid(gFont, "Quit", hoverTextColor);
    if (hoverQuitSurface == nullptr) {
        std::cerr << "Unable to render hover quit surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }
    gHoverQuitTexture = SDL_CreateTextureFromSurface(gRenderingWindow.getRenderer(), hoverQuitSurface);
    if (gHoverQuitTexture == nullptr) {
        std::cerr << "Unable to create texture from hover rendered quit! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(hoverQuitSurface);

    gStartRect = { 220, 150, 200, 50 };
    gOptionsRect = { 220, 250, 200, 50 };
    gQuitRect = { 220, 350, 200, 50 };
}
void Menu::handleEvents() {
    SDL_Event e;
    int x, y;
    SDL_GetMouseState(&x, &y);

    gMouseHoverStart = x > gStartRect.x && x < gStartRect.x + gStartRect.w && y > gStartRect.y && y < gStartRect.y + gStartRect.h;
    gMouseHoverOptions = x > gOptionsRect.x && x < gOptionsRect.x + gOptionsRect.w && y > gOptionsRect.y && y < gOptionsRect.y + gOptionsRect.h;
    gMouseHoverQuit = x > gQuitRect.x && x < gQuitRect.x + gQuitRect.w && y > gQuitRect.y && y < gQuitRect.y + gQuitRect.h;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            if (gMouseHoverStart) {
                startGame = true;
            } else if (gMouseHoverOptions) {
                openOptions = true;
            } else if (gMouseHoverQuit) {
                quit = true;
            }
        }
    }
}

void Menu::render() {
     SDL_Renderer* renderer = gRenderingWindow.getRenderer();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set to white
    SDL_RenderClear(renderer);

    SDL_Texture* currentTexture;
    SDL_Rect* currentRect;

    // Start Game
    currentTexture = gMouseHoverStart ? gHoverTextTexture : gTextTexture;
    currentRect = &gStartRect;
    SDL_RenderCopy(renderer, currentTexture, nullptr, currentRect);

    // Options
    currentTexture = gMouseHoverOptions ? gHoverOptionsTexture : gOptionsTexture;
    currentRect = &gOptionsRect;
    SDL_RenderCopy(renderer, currentTexture, nullptr, currentRect);

    // Quit
    currentTexture = gMouseHoverQuit ? gHoverQuitTexture : gQuitTexture;
    currentRect = &gQuitRect;
    SDL_RenderCopy(renderer, currentTexture, nullptr, currentRect);

    SDL_RenderPresent(renderer);
}

void Menu::close() {
    SDL_DestroyTexture(gTextTexture);
    SDL_DestroyTexture(gHoverTextTexture);
    SDL_DestroyTexture(gOptionsTexture);
    SDL_DestroyTexture(gHoverOptionsTexture);
    SDL_DestroyTexture(gQuitTexture);
    SDL_DestroyTexture(gHoverQuitTexture);

    gTextTexture = nullptr;
    gHoverTextTexture = nullptr;
    gOptionsTexture = nullptr;
    gHoverOptionsTexture = nullptr;
    gQuitTexture = nullptr;
    gHoverQuitTexture = nullptr;

    if (gFont) {
        TTF_CloseFont(gFont);
        gFont = nullptr;
    }
}
bool Menu::GetQuit()
{
    return quit;
}
void Menu::SetQuit(bool set)
{
    quit = set;
}

bool Menu::GetStartGame()
{
    return startGame;
}
void Menu::SetStartGame(bool set) {
    startGame = set;
    if (set == false) {
        // Reset menu states
        openOptions = false;
        quit = false;
        gMouseHoverStart = false;
        gMouseHoverOptions = false;
        gMouseHoverQuit = false;
    }
}
bool Menu::GetOpenOptions()
{
    return openOptions;
}

void Menu::LogSetStartGame()
{
    if(startGame){std::cout << "startGame : True\n";}
    if(!startGame){std::cout << "startGame : False\n";}
}