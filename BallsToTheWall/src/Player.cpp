#include "Player.h"
#include "core\Window.h"
#include "math/math.h"
#include <iostream>
#include "InputManager.h"
#include "Ball.h"
#include "input\Mouse.h"
#include "TimeTracker.h"
#include "Healthbar.h"
#include "SaveLoad.h"

sf::ConvexShape Player::myShape = sf::ConvexShape(3);
sf::ConvexShape Player::myShapeDir = sf::ConvexShape(3);
bool Player::myButtonPressedFlag = false;
float Player::myButtonTime = 0;
float Player::myCoyoteTime = 0.1f;
float Player::myBallLikeness = 0.7f;
float Player::myBallDistance = 10000;
sf::Vector2f Player::myCurrentVelocity = sf::Vector2f(0, 0);
float Player::myMaxVelocity = 600;
float Player::myAcceleration = 3000;
float Player::myLerpDecelerationPercent = 8.f;
float Player::myTurnSpeedMultiplier = 5;
bool Player::myDeadFlag = false;
float Player::myScoreMultiplier = 1;
int Player::myScore = 0;
float Player::myTimeScore = 0;
sf::Font Player::myScoreFont = sf::Font();
sf::Text Player::myScoreText = sf::Text();


sf::Vector2f Player::GetPosition()
{
	return myShape.getPosition();
}

void Player::SetPosition(const sf::Vector2f& aPos)
{
	myShape.setPosition(aPos);
}

sf::ConvexShape Player::GetShape()
{
	return myShape;
}

float Player::GetScoreMultiplier()
{
	return myScoreMultiplier;
}

void Player::AddScore(int aVal)
{
	myScore += aVal;
}

sf::Font& Player::GetScoreFont()
{
	return myScoreFont;
}

int Player::GetScore()
{
	return myScore;
}

void Player::OnStart()
{
	myScoreFont.loadFromFile("Assets/ScoreFont.ttf");

	myScoreText.setString(std::to_string(myScore));
	myScoreText.setFont(myScoreFont);
	myScoreText.setCharacterSize(40);

	myShape.setPoint(0, sf::Vector2f(0, -12.5f));
	myShape.setPoint(1, sf::Vector2f(12.5f, 12.5f));
	myShape.setPoint(2, sf::Vector2f(-12.5f, 12.5f));
	myShape.setPosition(sf::Vector2f(0, 0));
	myShape.setFillColor(sf::Color(0, 200, 200));

	myShapeDir.setPoint(0, sf::Vector2f(0, -12.5f));
	myShapeDir.setPoint(1, sf::Vector2f(5, -3));
	myShapeDir.setPoint(2, sf::Vector2f(-5, -3));
	myShapeDir.setPosition(sf::Vector2f(0, 0));
	myShapeDir.setFillColor(sf::Color(200, 100, 0));
}

void Player::OnUpdate()
{

	if (myDeadFlag)
		return;

	//Point towards mouse
	sf::Vector2f tempMouseVec = myShape.getPosition() - Mouse::GetPosition();
	float tempAngle = Math::ToDegrees(std::atan2(tempMouseVec.y, tempMouseVec.x));
	myShape.setRotation(tempAngle - 90);

	//determine moving direction
	sf::Vector2f tempDir;
	if (InputManager::GetKey(sf::Keyboard::W))
	{
		tempDir += sf::Vector2f(0, -1);
	}
	if (InputManager::GetKey(sf::Keyboard::S))
	{
		tempDir += sf::Vector2f(0, 1);
	}
	if (InputManager::GetKey(sf::Keyboard::A))
	{
		tempDir += sf::Vector2f(-1, 0);
	}
	if (InputManager::GetKey(sf::Keyboard::D))
	{
		tempDir += sf::Vector2f(1, 0);
	}

	myCurrentVelocity += Math::Normalized(tempDir) * sf::Vector2f((myCurrentVelocity.x < 0 != tempDir.x < 0) ? myTurnSpeedMultiplier : 1, (myCurrentVelocity.y < 0 != tempDir.y < 0) ? myTurnSpeedMultiplier : 1) * myAcceleration * TimeTracker::GetDeltaTime();

	if (tempDir.x == 0)
	{
		myCurrentVelocity = sf::Vector2f(Math::Lerp(myCurrentVelocity.x, 0, myLerpDecelerationPercent * TimeTracker::GetDeltaTime()), myCurrentVelocity.y);

	}
	if (tempDir.y == 0)
	{
		myCurrentVelocity = sf::Vector2f(myCurrentVelocity.x, Math::Lerp(myCurrentVelocity.y, 0, myLerpDecelerationPercent * TimeTracker::GetDeltaTime()));
	}

	if (Math::Length(myCurrentVelocity) > myMaxVelocity)
	{
		myCurrentVelocity = Math::Normalized(myCurrentVelocity) * myMaxVelocity;
	}

	//move the player accordingly
	myShape.setPosition(myShape.getPosition() + myCurrentVelocity * TimeTracker::GetDeltaTime());


	InputManager::GetMouseButtonDown(sf::Mouse::Left);
	myButtonTime += TimeTracker::GetDeltaTime();
	sf::Vector2f tempBallVec = myShape.getPosition() - Ball::GetPosition();
	sf::Vector2f tempMouseVecN = Math::Normalized(tempMouseVec);
	sf::Vector2f tempBallVecN = Math::Normalized(tempBallVec);
	if (Math::LengthSqrd(tempBallVec) <= myBallDistance && Math::Dot(tempBallVecN, tempMouseVecN) >= myBallLikeness)
	{
		myShapeDir.setFillColor(sf::Color(0, 255, 0));
		if (InputManager::GetMouseButtonDown(sf::Mouse::Left))
		{
			Healthbar::Reset();
			Ball::Hit(std::atan2((tempMouseVecN.y + tempBallVecN.y) / 2, (tempMouseVecN.x + tempBallVecN.x) / 2) - Math::Pi);
			myButtonPressedFlag = true;
		}
	}
	else
	{
		myShapeDir.setFillColor(sf::Color(200, 100, 0));
	}
	if (myButtonTime > myCoyoteTime)
	{
		myButtonPressedFlag = true;
	}

	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		myButtonPressedFlag = false;
		myButtonTime = 0;
	}
	myShape.setScale(0.7f, 0.7f);
	if (Ball::Intersects(myShape) && Ball::GetVelocity() != sf::Vector2f(0,0))
	{
		myShape.setScale(1, 1);
		Die();
	}
	myShape.setScale(1, 1);

	myScoreText.setPosition(sf::Vector2f(-myScoreText.getLocalBounds().width / 2, -Window::GetSize().y / 2));
	if (Ball::GetVelocity() != sf::Vector2f(0, 0))
	{
		myTimeScore += TimeTracker::GetDeltaTime() * 10;
		while (myTimeScore > 1)
		{
			myTimeScore--;
			myScore++;
		}
	}

}

void Player::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(myShape);
	myShapeDir.setRotation(myShape.getRotation());
	myShapeDir.setPosition(myShape.getPosition());
	aWindow->draw(myShapeDir);

	myScoreText.setString("Score: " + std::to_string(myScore));
	aWindow->draw(myScoreText);

	//Player to Mouse
	//Window::CurrentWindow->DrawLine(myShape.getPosition(), Mouse::GetPosition(), sf::Color::Red);

	////Player to Ball

	//sf::Color tempColor = sf::Color::Red;
	//sf::Vector2f tempMouseVec = myShape.getPosition() - Mouse::GetPosition();
	//sf::Vector2f tempBallVec = myShape.getPosition() - Ball::GetPosition();

	//if (Math::LengthSqrd(tempBallVec) <= myBallDistance && Math::NDot(tempBallVec, tempMouseVec) >= myBallLikeness)
	//{
	//	tempColor = sf::Color::Green;
	//}
	//Window::CurrentWindow->DrawLine(myShape.getPosition(), Ball::GetPosition(), tempColor);

}


void Player::Die()
{
	myDeadFlag = true;
	TimeTracker::SetTimeScale(0);
}

bool Player::GetDeadFlag()
{
	return myDeadFlag;
}
