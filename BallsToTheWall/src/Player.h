#pragma once
#include "SFML/Graphics.hpp"
class Player
{
public:
	static void OnStart();
	static void OnUpdate(const float& aDeltaTime);
	static void OnRender(sf::RenderWindow* aWindow);

private: 
	static sf::ConvexShape myShape;
	static float mySpeed;
	static bool myButtonPressedFlag;
	static float myButtonTime;
	static float myCoyoteTime;
	static float myBallLikeness;
	static float myBallDistance;

	static sf::Vector2f myCurrentVelocity;
	static float myMaxVelocity;
	static float myAcceleration;
};

