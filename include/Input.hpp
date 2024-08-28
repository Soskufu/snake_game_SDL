#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <iostream>
class Input {
public:
    // Initialize input states
    void Initialize();

    // Update the state of inputs using SDL_PumpEvents (only updates the state, does not handle specific events)
    void UpdateState();

    // Update the state of inputs using SDL_PollEvent (handles specific events)
    void ProcessEvents();

    // Check if a key is currently pressed
    bool IsKeyPressed(SDL_Scancode key) const;

    // Check if a mouse button is currently pressed
    bool IsMouseButtonPressed(Uint8 button) const;

    // Get mouse position
    void GetMousePosition(int& x, int& y) const;

    // Access the last polled event, useful for custom event handling
    SDL_Event GetLastEvent() const;

    
private:
    // Stores the state of all keys
    std::unordered_map<SDL_Scancode, bool> keyStates;

    // Stores the state of all mouse buttons
    std::unordered_map<Uint8, bool> mouseButtonStates;

    // Mouse position
    int mouseX, mouseY;

    // Last event polled by SDL_PollEvent
    SDL_Event lastEvent = {0};

};
