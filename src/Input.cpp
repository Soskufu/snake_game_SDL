#include <SDL2/SDL.h>
#include "Input.hpp"

void Input::Initialize() {
    keyStates.clear();
    mouseButtonStates.clear();
    mouseX = 0;
    mouseY = 0;
}

void Input::ProcessEvents() {
   while (SDL_PollEvent(&lastEvent)) {
        // Check for SDL_QUIT event and handle it immediately
       if (lastEvent.type == SDL_QUIT) {
            //quit = true; // or set a flag that you check in your main loop
            break; // Exit the loop as soon as SDL_QUIT is found
        }

        // Update input states based on events
        if (lastEvent.type == SDL_KEYDOWN) {
            keyStates[lastEvent.key.keysym.scancode] = true;
        } else if (lastEvent.type == SDL_KEYUP) {
            keyStates[lastEvent.key.keysym.scancode] = false;
        }

        if (lastEvent.type == SDL_MOUSEBUTTONDOWN) {
            mouseButtonStates[lastEvent.button.button] = true;
        } else if (lastEvent.type == SDL_MOUSEBUTTONUP) {
            mouseButtonStates[lastEvent.button.button] = false;
        }

        //std::cout << "Event type: " << lastEvent.type << std::endl;
    }
}

void Input::UpdateState() {
    SDL_PumpEvents();  // Update SDL's internal event state

    // Update key states
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    for (const auto& keyState : keyStates) {
        keyStates[keyState.first] = currentKeyStates[keyState.first];
    }

    // Update mouse button states
    int mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    for (const auto& buttonState : mouseButtonStates) {
        mouseButtonStates[buttonState.first] = mouseState & SDL_BUTTON(buttonState.first);
    }
}

bool Input::IsKeyPressed(SDL_Scancode key) const {
    std::unordered_map<SDL_Scancode, bool>::const_iterator it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}

bool Input::IsMouseButtonPressed(Uint8 button) const {
    std::unordered_map<Uint8, bool>::const_iterator it = mouseButtonStates.find(button);
    return it != mouseButtonStates.end() && it->second;
}

void Input::GetMousePosition(int& x, int& y) const {
    x = mouseX;
    y = mouseY;
}

SDL_Event Input::GetLastEvent() const {
    return lastEvent;

}