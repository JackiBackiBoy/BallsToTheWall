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
	static sf::Vector2f GetVelocity();
	static sf::CircleShape GetShape();
	static bool Intersects(const sf::ConvexShape& aPolygon);
private:
	static sf::CircleShape myShape;
	static sf::Vector2f myDirection;
	static float myVelocity;
};

