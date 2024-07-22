#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

bool running = true;

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Rect head {500,500,30,30},apple{0,0,30,30};
std::deque<SDL_Rect> Snakebody; //snake body container
unsigned int size = 0;
enum Directions {up = 1,down,left,right};

void createWindow()
{
	if (SDL_CreateWindowAndRenderer(1000, 1000, 0, &window, &renderer) < 0)
	{ 
		std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
	}
    SDL_SetWindowTitle(window, "SnakeGame");
}
void render()
{

SDL_SetRenderDrawColor(renderer,255,255,255,255);
		SDL_RenderFillRect(renderer, &head);
		

SDL_RenderFillRect(renderer, &apple);
for(auto snake_segment : Snakebody)
	{SDL_RenderFillRect(renderer, &snake_segment);
	};

SDL_RenderPresent(renderer);
SDL_SetRenderDrawColor(renderer,0,0,0,255);
SDL_RenderClear(renderer);
}
void gen_apple()
{   
	int randomX = rand() % 900;
    int randomY = rand() % 900;
    apple.x = randomX;
    apple.y = randomY;
}
void startover(int &move) {
   head.x = 500;
   head.y = 500;
   move = 0;
   size = 0;
   gen_apple();
 }

void input(int &move)
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT) running = false;
			const Uint8* keystates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) running = false;
    if (keystates[SDL_SCANCODE_ESCAPE]) running = false;
    if (keystates[SDL_SCANCODE_W]) if (move != down) move = up;
    if (keystates[SDL_SCANCODE_S]) if (move != up) move = down;
    if (keystates[SDL_SCANCODE_A]) if (move != right) move = left;
    if (keystates[SDL_SCANCODE_D]) if (move != left )move = right;  
		}
}

void logic(int &move)
{
	switch(move)
		{
			case down: head.y += 10; break;
			case up: head.y -= 10; break;
			case left: head.x -= 10; break;
			case right: head.x += 10; break;
		};
}
void update(int &move) {    
    if (SDL_HasIntersection(&apple, &head)) {
        gen_apple();
        if(size == 0)
        {
        size += 2;
        } 
        else{}size++;
    }
    //collision detection with snake body
    for(auto snake_segment : Snakebody){ 
			if(head.x == snake_segment.x && head.y == snake_segment.y)
			{
				startover(move);	
			}
		};
    //add newest head to the snake
	Snakebody.push_front(head);
	while(Snakebody.size() > size)
	Snakebody.pop_back();
    
    if (head.x < 0) startover(move);//head.x +=1000;
    if (head.x > 1000) startover(move);//head.x -=1000;
    if (head.y < 0) startover(move); //head.y +=1000;
    if (head.y > 1000) startover(move); //head.y -=1000;
}

int WinMain(int argc,char* args[])
{
	int move = 0;
	createWindow();
	gen_apple();
	while(running)
	{
		input(move);
		logic(move);
		update(move);
		render();//draw Body
		SDL_Delay(25);
	}
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
	
}
