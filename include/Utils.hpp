#pragma once
#include <SDL2/SDL.h>

namespace utils
{
	inline float hireTimeInSeconds()
	{
		float t = SDL_GetTicks();
		t *= 0.001f; //scales up to seconds
		return t;
	}
}

