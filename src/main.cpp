#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <deque>
#include <ctime>
#include <cmath>
#include "RenderingWindow.hpp"
#include "TextureManager.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "Utils.hpp"
#include "Render.hpp"
#include "Config.hpp"
#include "Menu.hpp"
RenderingWindow window;
TextureManager textureManager;
Audio gamesound;
Input p1;
FontManager fontmanage(window.getRenderer());
Config config;
Render nRender(window.getRenderer());
Menu menu(window,p1,fontmanage);

SDL_Rect head {12 * config.CELL_SIZE, 12 * config.CELL_SIZE, config.CELL_SIZE, config.CELL_SIZE};
SDL_Rect apple {0, 0, config.CELL_SIZE, config.CELL_SIZE};
std::deque<SDL_Rect> snakeSegments; // Use deque to store snake segments
int currentDirection = config.Right;
int nextDirection = config.Right;
float moveCounter = config.SNAKE_BASE_SPEED;
bool gameOver = false;
bool quit = false;
bool pause = true;

int score = 0;
// Function prototypes
void loadTexture();
void render();
void startOver();
void input();
void logic();
void update(float deltaTime);
void tryDirection(int direction);
bool intersectsSnake(const SDL_Rect& position, bool countHead = true);
void generateApple();
void renderHeadTexture();

// Load textures
void loadTexture() {
    textureManager.LoadTexture("snakeU" ,"res/gfx/snake1.png", window.getRenderer());
    textureManager.LoadTexture("snakeR","res/gfx/snake2.png",window.getRenderer());
    textureManager.LoadTexture("snakeL","res/gfx/snake3.png",window.getRenderer());
    textureManager.LoadTexture("snakeD","res/gfx/snake4.png",window.getRenderer());
    textureManager.LoadTexture("apple_png","res/gfx/apple.png",window.getRenderer());
    textureManager.LoadTexture("body","res/gfx/snakebody.png",window.getRenderer());
    textureManager.LoadTexture("backgroundTexture","res/gfx/Snakegame_Sprite-0001.bmp",window.getRenderer());
   
}
void renderHeadTexture() {
	
    switch (currentDirection) {
        case config.Left:
            nRender.DrawTexture(window.getRenderer(), textureManager.GetTexture("snakeL"), &head);
            break;
        case config.Right:
            nRender.DrawTexture(window.getRenderer(), textureManager.GetTexture("snakeR"), &head);
            break;
        case config.Up:
            nRender.DrawTexture(window.getRenderer(), textureManager.GetTexture("snakeU"), &head);
            break;
        case config.Down:
            nRender.DrawTexture(window.getRenderer(), textureManager.GetTexture("snakeD"), &head);
            break;
    }
}

// Render game elements
void render() {
	
    //SDL_RenderClear(window.getRenderer());
    nRender.Clear();


    // Render background
    nRender.DrawTexture(window.getRenderer(), textureManager.GetTexture("backgroundTexture"));

    // Render snake body segments
    nRender.DrawColor(window.getRenderer(), 0, 255, 0, 255);
    for (size_t i = 1; i < snakeSegments.size(); ++i) { 
    	nRender.DrawTexture(window.getRenderer(), textureManager.GetTexture("body"),&snakeSegments[i]);
    }
    // Render snake head
    renderHeadTexture();
     nRender.DrawTexture(window.getRenderer(),textureManager.GetTexture("apple_png"), &apple);
    nRender.Present(window.getRenderer());
}

// Reset the game
void startOver() {
    head.x = 12 * config.CELL_SIZE;
    head.y = 12 * config.CELL_SIZE;
    snakeSegments.clear();
    snakeSegments.push_back(head);
    snakeSegments.push_front(head);
    snakeSegments.push_front(head);
    moveCounter = config.SNAKE_BASE_SPEED;
    score = 0;
    generateApple(); // Initialize apple position
    currentDirection = config.Right; // Reset direction
    nextDirection = config.Right;    // Reset next direction
}

// Handle input
void input() {
	
	
	p1.ProcessEvents();
	
       if(p1.GetLastEvent().type == SDL_QUIT || p1.IsKeyPressed(SDL_SCANCODE_ESCAPE))
        {
            	quit = true;
            }
        if (p1.IsKeyPressed(SDL_SCANCODE_W)) { tryDirection(config.Up);}
        if (p1.IsKeyPressed(SDL_SCANCODE_S)) { tryDirection(config.Down);}
        if (p1.IsKeyPressed(SDL_SCANCODE_A)) { tryDirection(config.Left);}
        if (p1.IsKeyPressed(SDL_SCANCODE_D)) { tryDirection(config.Right);}
        
    }

// Try adding new direction
void tryDirection(int direction) {
    if ((currentDirection == config.Left && direction != config.Right) ||
        (currentDirection == config.Right && direction != config.Left) ||
        (currentDirection == config.Up && direction != config.Down) ||
        (currentDirection == config.Down && direction != config.Up)) {
        nextDirection = direction;
    }
}

// Update game state
void logic() {
    if (nextDirection != currentDirection) {
        currentDirection = nextDirection;
    }

    SDL_Rect nextHeadPosition = head;

    if (currentDirection == config.Left) nextHeadPosition.x -= config.CELL_SIZE; 
    if (currentDirection == config.Right) nextHeadPosition.x += config.CELL_SIZE; 
    if (currentDirection == config.Up) nextHeadPosition.y -= config.CELL_SIZE;
    if (currentDirection == config.Down) nextHeadPosition.y += config.CELL_SIZE;

    head = nextHeadPosition;
    snakeSegments.push_front(head);

    if (intersectsSnake(apple)) {
        score++;
        generateApple(); // Generate new apple position
        
    } else {
        snakeSegments.pop_back(); // Remove the tail segment
    }

    if (head.x < 0 || head.x >= window.getWidth() || head.y < 0 || head.y >= window.getHeight()) {
        startOver();
    }

    if (intersectsSnake(head, false)) {
        startOver();
    }
}

// Update function with deltaTime
void update(float deltaTime) {
    moveCounter -= deltaTime;

    if (moveCounter <= 0) {
        logic();
        moveCounter = config.SNAKE_BASE_SPEED - (score * config.SPEED_BUMP);
        moveCounter = std::max(moveCounter, config.SNAKE_MAX_SPEED); //takes the bigger number of the two
        
    }
}

// Check if position intersects with snake
bool intersectsSnake(const SDL_Rect& position, bool countHead) {
    for (size_t i = 0; i < snakeSegments.size(); i++) {
        if (snakeSegments[i].x == position.x && snakeSegments[i].y == position.y) {
            if (!countHead && i == 0) continue;
            return true;
        }
    }
    return false;
}

// Generate a new apple position
void generateApple() {
	int chance = rand() % 10;
	if(chance >= 5 && score > 0)
	{
		gamesound.PlaySound("Cheezburger");
	}
	else if(score > 0){gamesound.PlaySound("Nom Nom");}
    SDL_Rect newPosition;
    do {
        newPosition.x = (rand() % (window.getWidth() / config.CELL_SIZE)) * config.CELL_SIZE;
        newPosition.y = (rand() % (window.getHeight() / config.CELL_SIZE)) * config.CELL_SIZE;
        newPosition.w = config.CELL_SIZE;
        newPosition.h = config.CELL_SIZE;
    } while (intersectsSnake(newPosition));
    apple = newPosition;
}



// Entry point
int WinMain(int argc, char* args[]) {
    srand(time(NULL));
    window.initialize("snakegame",900,900);
    p1.Initialize();
    gamesound.SetVolume(20);
    gamesound.LoadSound("Cheezburger","res/sfx/audio/wav/ROBLOX Mmm... Cheezburger Sound Effect.wav");
    gamesound.LoadSound("Nom Nom","res/sfx/audio/wav/Roblox Nom Nom Nom Sound Effect.wav");
    gamesound.LoadMusic("Adventure","res/sfx/audio/mp3/Sneaky Adventure - Background Music (HD).mp3");
    gamesound.PlayMusic("Adventure" , -1);
    loadTexture();
    menu.loadMedia();
    
    startOver();

    float lastTime = SDL_GetTicks();
    float deltaTime = 0;

    while (!quit) { 
    
	float currentTime = SDL_GetTicks();
        
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        input();
        if (!gameOver) {
            update(deltaTime);
        }
        render();
       
    }
      
        
    
    SDL_Quit();

    return 0;
}
