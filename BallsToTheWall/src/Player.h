#pragma once
#include "SFML/Graphics.hpp"
class Player
{
public:
	static void OnStart();
	static void OnUpdate();
	static void OnRender(sf::RenderWindow* aWindow);
	static sf::Vector2f GetPos();
	static void Die();
	static bool GetDeadFlag();

private: 
	static bool myDeadFlag;
	static sf::ConvexShape myShape;
	static bool myButtonPressedFlag;
	static float myButtonTime;
	static float myCoyoteTime;
	static float myBallLikeness;
	static float myBallDistance;

	static sf::Vector2f myCurrentVelocity;
	static float myMaxVelocity;
	static float myAcceleration;
	static float myLerpDecelerationPercent;
	static float myTurnSpeedMultiplier;

};

