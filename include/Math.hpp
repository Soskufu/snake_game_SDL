#pragma once
#include <iostream>

class Vector2f //easier to keep track of cordinates
{
public:
	Vector2f()
	:x(0.0f), y(0.0f) //: faster way of setting variable equal to parameter (:) = (=)
	{}

	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y)
	{}

	void print() // useful for debugging
	{
		std::cout << x << ", " << y << std::endl;
	}
	
	float x, y;
};