#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <deque>

bool running = true;
float SNAKE_BASE_SPEED = 0.2f;
float SNAKE_MAX_SPEED = 0.05f;
float SPEED_BUMP = 0.005f;
SDL_Renderer* renderer;
SDL_Window* window;
int width = 900;
int height = 900;
int CELL = 30;
SDL_Rect head {10 * CELL,10 * CELL,CELL,CELL},apple{0,0,CELL,CELL};
std::deque<SDL_Rect> Snakebody; //snake body container
unsigned int size = 1;
int score = 0;
float moveCounter = SNAKE_BASE_SPEED;
enum Directions {up = 1,down,left,right};

struct Timestep
{
public:
	Timestep(float time = 0.0f)
	: m_Time(time)
	{

	}
	float GetSeconds() const { return m_Time/1000;}
	float GetMilliseconds() const{return m_Time;}
private:
	float m_Time;
};

void createWindow()
{
	if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0)
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
{   while(SDL_HasIntersection(&apple, &head))
{
	int randomX = rand() % (width/ CELL) * CELL;
	//randomX *= rand() % 30;
    int randomY = rand() % (height/ CELL) * CELL; 
    //randomY *= rand() % 30;
    apple.x = randomX;
    apple.y = randomY;
    size++;
}
}



void startover(int &move) 
{
   head.x = width/2;
   head.y = height/2;
   move = 0;
   score = 0;
   size = 1;
   SNAKE_BASE_SPEED = 0.2f;
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
			case down: head.y += CELL; break;
			case up: head.y -= CELL; break;
			case left: head.x -= CELL; break;
			case right: head.x += CELL; break;
		};
		/* if (SDL_HasIntersection(&apple, &head)) {
        //speed += speedbump;
        gen_apple();
        score++;
    }*/
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
	{
	Snakebody.pop_back();
    }
    if (head.x < 0)  startover(move);////head.x +=1000;
    if (head.x > width)  startover(move);//head.x-=1000;
    if (head.y < 0)  startover(move); //head.y +=1000;
    if (head.y > height)  startover(move); //head.y-=1000;
}
void update(int & move,Timestep ts) {
    moveCounter -= ts.GetSeconds();

    if (moveCounter <= 0) {
        logic(move);
        moveCounter = SNAKE_BASE_SPEED - (size * SPEED_BUMP);
        moveCounter = std::max(moveCounter, SNAKE_MAX_SPEED); //takes the bigger number of the two
        std::cout << moveCounter << std::endl;
    }
}
void vector2f(SDL_Rect bob)
{
	int x = bob.x/30.0;
	int y = bob.y/30.0;
	std::cout << "(" << x << "," << y << ")\n";
}
int WinMain(int argc,char* args[])
{
	
	float m_LastFrameTime = SDL_GetTicks();
	int move = 0;
	createWindow();
	gen_apple();
	while(running)
	{
		float time = (float)SDL_GetTicks(); //current frametime
		Timestep timestep = (time - m_LastFrameTime);//deltatime
		m_LastFrameTime = time;//record last frametime
		std::cout << timestep.GetSeconds() << std::endl;
		input(move);
		update(move,timestep);
		gen_apple();
		render();//draw Body
		SDL_Delay(17);
	}
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
	
}
