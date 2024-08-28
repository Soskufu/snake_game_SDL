#include "Snake.hpp"
	Snake::Snake()
{
		SDL_Rect head {12 * config.CELL_SIZE, 12 * config.CELL_SIZE, config.CELL_SIZE, config.CELL_SIZE};;
		SDL_Rect apple {0, 0, config.CELL_SIZE, config.CELL_SIZE};
	}
	void Snake::tryDirection(int direction) {
    if ((currentDirection == config.Left && direction != config.Right) ||
        (currentDirection == config.Right && direction != config.Left) ||
        (currentDirection == config.Up && direction != config.Down) ||
        (currentDirection == config.Down && direction != config.Up)) {
        nextDirection = direction;
    }
}
	void Snake::Grow()
	{
		snakeSegments.push_front(head);
	}
	void Snake::Shrink()
	{
		snakeSegments.pop_back(); // Remove the tail segment
	}


	void Snake::RepositionApple(){
    SDL_Rect newPosition;
    do {
        newPosition.x = (rand() % (window.getWidth() / config.CELL_SIZE)) * config.CELL_SIZE;
        newPosition.y = (rand() % (window.getHeight() / config.CELL_SIZE)) * config.CELL_SIZE;
        newPosition.w = config.CELL_SIZE;
        newPosition.h = config.CELL_SIZE;
    } while (intersectsSnake(newPosition));
    apple = newPosition;
}
	bool Snake::intersectsSnake(const SDL_Rect& position, bool countHead) {
    for (size_t i = 0; i < snakeSegments.size(); i++) {
        if (snakeSegments[i].x == position.x && snakeSegments[i].y == position.y) {
            if (!countHead && i == 0) continue;
            return true;
        }
    }
    return false;
}
	bool Snake::IsAlive(){
		return alive;

	}
	void Snake::SetAlive(bool status){
		alive = status;
	}
	void Snake::startOver() {
	SetAlive(true);
    head.x = 12 * config.CELL_SIZE;
    head.y = 12 * config.CELL_SIZE;
    snakeSegments.clear();
    snakeSegments.push_back(head);
    snakeSegments.push_front(head);
    snakeSegments.push_front(head);
    moveCounter = config.SNAKE_BASE_SPEED;
    RepositionApple(); // Initialize apple position
    currentDirection = config.Right; // Reset direction
    nextDirection = config.Right;    // Reset next direction
}
	void Snake::Update()
	{
		 if (nextDirection != currentDirection) {
        currentDirection = nextDirection;
    }

    SDL_Rect nextHeadPosition = head;

    if (currentDirection == config.Left) nextHeadPosition.x -= config.CELL_SIZE; 
    if (currentDirection == config.Right) nextHeadPosition.x += config.CELL_SIZE; 
    if (currentDirection == config.Up) nextHeadPosition.y -= config.CELL_SIZE;
    if (currentDirection == config.Down) nextHeadPosition.y += config.CELL_SIZE;

    head = nextHeadPosition;
    Grow();

    if (intersectsSnake(apple)) {
        //score++;
        RepositionApple(); // Generate new apple position
        
    } else {
        Shrink();
    }

    if (head.x < 0 || head.x >= window.getWidth() || head.y < 0 || head.y >= window.getHeight()) {
        SetAlive(false);
        startOver();
    }

    if (intersectsSnake(head, false)) {
        SetAlive(false);
        startOver();
    }
}
	