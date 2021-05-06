#pragma once
#include "SFML/Graphics.hpp"
class Player
{
public:
	static void OnStart();
	static void OnUpdate();
	static void OnRender(sf::RenderWindow* aWindow);
	static void Die();
	static bool GetDeadFlag();
	static sf::Vector2f GetPosition();
	static void SetPosition(const sf::Vector2f& aPos);
	static sf::ConvexShape GetShape();
	static float GetScoreMultiplier();
	static void AddScore(int aVal);
	static sf::Font& GetScoreFont();
	static int GetScore();
	static void Reset();
private: 
	static sf::Font myScoreFont;
	static sf::Text myScoreText;
	static bool myDeadFlag;
	static sf::ConvexShape myShape;
	static sf::ConvexShape myShapeDir;
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
	static float myScoreMultiplier;

	static int myScore;
	static float myTimeScore;
	static sf::Texture myTexture;

};

