#include "Player.h"
#include "core\Window.h"
#include "math/math.h"
#include <iostream>
#include "InputManager.h"
#include "Ball.h"
#include "input\Mouse.h"
sf::ConvexShape Player::myShape = sf::ConvexShape(3);
float Player::mySpeed = 500;
bool Player::myButtonPressedFlag = false;
float Player::myButtonTime = 0;
float Player::myCoyoteTime = 0.1f;
float Player::myBallLikeness = 0.7f;
float Player::myBallDistance = 10000;

void Player::OnStart()
{
	myShape.setPoint(0, sf::Vector2f(0, -12.5f));
	myShape.setPoint(1, sf::Vector2f(12.5f, 12.5f));
	myShape.setPoint(2, sf::Vector2f(-12.5f, 12.5f));
	myShape.setPosition(sf::Vector2f(0, 0));
}

void Player::OnUpdate(const float& aDeltaTime)
{


	//Point towards mouse
	sf::Vector2f tempMouseVec = myShape.getPosition() - Mouse::GetPosition();
	float tempAngle = Math::ToDegrees(std::atan2(tempMouseVec.y, tempMouseVec.x));
	myShape.setRotation(tempAngle -90);

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


	//move the player accordingly
	myShape.setPosition(myShape.getPosition() + Math::Normalized(tempDir) * mySpeed * aDeltaTime);


	//If hit ball pressed
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !myButtonPressedFlag)
	{
		myButtonTime += aDeltaTime;
		sf::Vector2f tempBallVec = myShape.getPosition() - Ball::GetPosition();
		if (Math::LengthSqrd(tempBallVec) <= myBallDistance && Math::NDot(tempBallVec, tempMouseVec) >= myBallLikeness)
		{
			Ball::Hit(Math::ToRadians(tempAngle-180) );
			myButtonPressedFlag = true;
		}
		if (aDeltaTime > myCoyoteTime) 
		{
			myButtonPressedFlag = true;
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		myButtonPressedFlag = false;
		myButtonTime = 0;
	}
}

void Player::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(myShape);

	sf::Vector2f tempMouseVec = myShape.getPosition() - Mouse::GetPosition();

	//Player to Mouse
	sf::VertexArray va = sf::VertexArray(sf::PrimitiveType::Lines, 2);
	va[0].color = sf::Color::Red;
	va[0].position = myShape.getPosition();
	va[1].color = sf::Color::Red;
	va[1].position = Mouse::GetPosition();
	aWindow->draw(va);

	//Player to Ball
	va = sf::VertexArray(sf::PrimitiveType::Lines, 2);
	sf::Vector2f tempBallVec = myShape.getPosition() - Ball::GetPosition();
	if (Math::LengthSqrd(tempBallVec) <= myBallDistance && Math::NDot(tempBallVec, tempMouseVec) >= myBallLikeness) {
		va[0].color = sf::Color::Green;
		va[1].color = sf::Color::Green;
	}
	else
	{
		va[0].color = sf::Color::Red;
		va[1].color = sf::Color::Red;
	}
	va[0].position = myShape.getPosition();
	va[1].position = Ball::GetPosition();
	aWindow->draw(va);
}
