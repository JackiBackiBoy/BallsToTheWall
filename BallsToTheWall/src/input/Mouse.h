#ifndef MOUSE_HEADER
#define MOUSE_HEADER

#include "core/Window.h"
#include "SFML/Window/Mouse.hpp"

class Mouse
{
public:
	~Mouse() {};

	static sf::Vector2f GetPosition();

private:
	Mouse() {};
};
#endif