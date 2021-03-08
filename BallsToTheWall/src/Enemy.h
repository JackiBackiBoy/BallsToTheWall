#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
class Enemy
{
public:
	Enemy(const int& aPointCount, const float& aRadius, const sf::Vector2f& aPosition, const float& aRotation);
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnRender(sf::RenderWindow* aWindow);
	void Die();
	bool IsDead();
	bool Intersects(sf::ConvexShape a);
	void Collision();
	sf::Vector2f GetPosition();
	void SetPosition(const sf::Vector2f& aPosition);
	void SetScale(const sf::Vector2f& aScale);
	sf::Vector2f GetVelocity();
	sf::ConvexShape GetShape();
protected:
	sf::ConvexShape myShape;
	sf::Vector2f myDirection;
	float myVelocity = 0;
private:
	bool myDeadFlag = false;
};

