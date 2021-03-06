#pragma once
#include "SFML/Graphics.hpp"
class Ball
{
public:
	static void OnStart();
	static void OnUpdate();
	static void OnRender(sf::RenderWindow* aWindow);
	static sf::Vector2f GetPosition();
	static void Hit(float anAngle);
private:
	static sf::CircleShape myShape;
	static sf::Vector2f myDirection;
	static float myVelocity;
};

