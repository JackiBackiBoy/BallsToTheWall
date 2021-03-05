#pragma once
#include "SFML/Graphics.hpp"
class Ball
{
public:
	static void OnStart();
	static void OnUpdate(const float& aDeltaTime);
	static void OnRender(sf::RenderWindow* aWindow);

private:
	static sf::CircleShape myShape;
	static sf::Vector2f myDirection;
	static float myVelocity;
};

