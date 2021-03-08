#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
class Enemy
{
public:
	Enemy(const int& aPointCount, const float& aRadius, const sf::Vector2f& aPosition);
	void OnStart();
	void OnUpdate();
	void OnRender(sf::RenderWindow* aWindow);
	void Die();
	bool IsDead();
	bool Intersects(sf::ConvexShape a);
	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();
private:
	sf::ConvexShape myShape;
	sf::Vector2f myDirection;
	float myVelocity = 0;
	bool myDeadFlag = false;
};

