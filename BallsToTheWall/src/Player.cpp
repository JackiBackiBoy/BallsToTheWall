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
#include "Button.h"

sf::ConvexShape Player::myShape = sf::ConvexShape(3);
bool Player::myButtonPressedFlag = false;
float Player::myButtonTime = 0;
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
sf::Texture Player::myTexture = sf::Texture();

float Player::myCoyoteTime = 0.1f;
float Player::myCoyoteTimer = 0;


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

void Player::Reset()
{
	myButtonTime = 0;
	myCurrentVelocity = sf::Vector2f(0, 0);
	myDeadFlag = false;
	myScoreMultiplier = 1;
	myScore = 0;
	myTimeScore = 0;
	myShape.setFillColor(sf::Color(255, 255, 255));
	if (Sandbox::GetPack() == "Fun")
	{
		myShape.setTexture(nullptr);
	}
	else
	{
		myTexture.loadFromFile("Assets/" + Sandbox::GetPack() + "Player.png");
		myShape.setTexture(&myTexture);
	}
	myShape.setTextureRect(sf::IntRect(0, 0, myTexture.getSize().x, myTexture.getSize().y));
}

void Player::OnStart()
{
	myScoreFont.loadFromFile("Assets/ScoreFont.ttf");

	myScoreText.setString(std::to_string(myScore));
	myScoreText.setFont(myScoreFont);
	myScoreText.setCharacterSize(40);

	myShape.setPoint(0, sf::Vector2f(0, -12.5f) * Sandbox::GetScaleFactor());
	myShape.setPoint(1, sf::Vector2f(12.5f, 12.5f) * Sandbox::GetScaleFactor());
	myShape.setPoint(2, sf::Vector2f(-12.5f, 12.5f) * Sandbox::GetScaleFactor());
	myShape.setPosition(sf::Vector2f(0, 0));
	myShape.setFillColor(sf::Color(255, 255, 255));
}

void Player::OnUpdate()
{
	if (Sandbox::GetPack() == "Fun")
	{
		myShape.setFillColor(Math::ShiftRainbow(myShape.getFillColor(), TimeTracker::GetUnscaledDeltaTime() * 500));
	}


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
	if (Math::LengthSqrd(tempBallVec / Sandbox::GetScaleFactor()) <= myBallDistance && Math::Dot(tempBallVecN, tempMouseVecN) >= myBallLikeness)
	{
		Ball::SetOutlineFlag(true);
		if ((InputManager::GetMouseButtonDown(sf::Mouse::Left) || myCoyoteTimer > 0) && !Button::GetHoverFlag())
		{
			Healthbar::Reset();
			Ball::Hit(std::atan2((tempMouseVecN.y + tempBallVecN.y) / 2, (tempMouseVecN.x + tempBallVecN.x) / 2) - Math::Pi);
			myButtonPressedFlag = true;
			myCoyoteTimer = 0;
		}
	}
	else
	{
		Ball::SetOutlineFlag(false);
	}
	
	if (InputManager::GetMouseButtonDown(sf::Mouse::Left) && !Button::GetHoverFlag())
	{
		myCoyoteTimer = myCoyoteTime;
	}
	else
	{
		myCoyoteTimer -= TimeTracker::GetDeltaTime();
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
	if (Ball::Intersects(myShape) && Ball::GetVelocity() != sf::Vector2f(0, 0))
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

	myScoreText.setString("Score: " + std::to_string(myScore));
	if (Sandbox::GetPack() == "Fun")
	{
		myScoreText.setFillColor(Math::ShiftRainbow(myScoreText.getFillColor(), TimeTracker::GetUnscaledDeltaTime() * 800));
	}	
	else
	{
		myScoreText.setFillColor(sf::Color::White);
	}
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
