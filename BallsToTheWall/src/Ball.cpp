#include "Ball.h"
#include "core/Window.h"
#include "math/Math.h"
#include <Player.h>
#include "TimeTracker.h"

sf::CircleShape Ball::myShape = sf::CircleShape(10);

sf::Vector2f Ball::myDirection = sf::Vector2f(0, 0);
float Ball::myVelocity = 5;

void Ball::OnStart()
{
	myShape.setPosition(sf::Vector2f(200, 0));
	myShape.setOrigin(sf::Vector2f(myShape.getLocalBounds().width / 2, myShape.getLocalBounds().height / 2));
	myDirection = Math::Normalized(sf::Vector2f(3, 7));
	//myShape.setFillColor(sf::Color(200, 255, 255));
	myShape.setFillColor(sf::Color::Magenta);
}

void Ball::OnUpdate()
{
	//calculate new pos
	sf::Vector2f tempNewPos = myShape.getPosition() + myDirection * myVelocity * TimeTracker::GetDeltaTime();

	//check if new pos is inside the screen
	if (tempNewPos.x < -(int)Window::CurrentWindow->GetRawWindow()->getSize().x / 2 && myDirection.x < 0)
	{
		myDirection.x *= -1;
	}
	if (tempNewPos.x + 20 > Window::CurrentWindow->GetRawWindow()->getSize().x / 2 && myDirection.x > 0)
	{
		myDirection.x *= -1;
	}
	if (tempNewPos.y < -(int)Window::CurrentWindow->GetRawWindow()->getSize().y / 2 && myDirection.y < 0)
	{
		myDirection.y *= -1;
	}
	if (tempNewPos.y + 20 > Window::CurrentWindow->GetRawWindow()->getSize().y / 2 && myDirection.y > 0)
	{
		myDirection.y *= -1;
	}

	//recalculate new pos
	myShape.setPosition(myShape.getPosition() + myDirection * myVelocity * TimeTracker::GetDeltaTime());

	if (Math::Distance(myShape.getPosition(), Player::GetPosition()) < 15)
	{
		Player::Die();
	}
}

void Ball::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(myShape);
}

sf::Vector2f Ball::GetPosition()
{
	return myShape.getPosition();
}

void Ball::Hit(float anAngle)
{
	myDirection = sf::Vector2f(std::cos(anAngle), std::sin(anAngle));
	myVelocity += 100;
}
