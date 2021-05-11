#ifndef MOUSE_HEADER
#define MOUSE_HEADER

#include "core/Window.h"
#include "SFML/Window/Mouse.hpp"

class Mouse
{
public:
	~Mouse() {};

	static sf::Vector2f GetPosition(bool aScaledFlag = true);

	static void SetPosition(const sf::Vector2i& aPos);

private:
	Mouse() {};
};
#endif