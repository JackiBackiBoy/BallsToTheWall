#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "Player.h"
#include "TimeTracker.h"
#include "math\Math.h"
#include "Ball.h"
#include "Random.h"
#include "core\Window.h"

class Enemy
{
public:
	Enemy(const int& aPointCount, const float& aRadius, const sf::Vector2f& aPosition, const float& aRotation);
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnRender(sf::RenderWindow* aWindow);
	virtual void Die();
	bool IsDead();
	bool Intersects(sf::ConvexShape a);
	void Collision();
	sf::Vector2f GetPosition();
	void SetPosition(const sf::Vector2f& aPosition);
	void SetScale(const sf::Vector2f& aScale);
	void SetRotation(const float& someDegrees);
	void Rotate(const float& someDegrees);
	sf::Vector2f GetVelocity();
	sf::ConvexShape GetShape();
	int GetScore();
	sf::Color GetFillColor();
	void SetFillColor(sf::Color aColor);
protected:
	sf::ConvexShape myShape;
	sf::Vector2f myDirection;
	float myVelocity = 0;
	int myScore = 300;
	bool myStarting = 1;
private:
	bool myDeadFlag = false;
};

