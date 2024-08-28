#pragma once
#include<SDL2/SDL.h>
#include <deque>
#include "config.hpp"
#include "RenderingWindow.hpp"

class Snake
{
public:
	Snake();
	void tryDirection(int direction);
	void Grow();
	void Shrink();
	void RepositionApple();
	bool IsAlive();
	void SetAlive(bool status);
	bool intersectsSnake(const SDL_Rect& position, bool countHead = true);
	void Update();
	void startOver();
private:
	SDL_Rect head;
	SDL_Rect apple;
	std::deque<SDL_Rect>  snakeSegments;
	Config config;
	RenderingWindow window;
	int currentDirection = config.Right;
	int nextDirection = config.Right;
	float moveCounter = config.SNAKE_BASE_SPEED;
	bool alive;
};