#include "Ball.h"
#include "core/Window.h"
#include "math/Math.h"

sf::CircleShape Ball::myShape = sf::CircleShape(10);

sf::Vector2f Ball::myDirection = sf::Vector2f(0,0);
float Ball::myVelocity = 5;

void Ball::OnStart()
{
	myShape.setPosition(sf::Vector2f(0, 0));
	myDirection = Math::Normalized(sf::Vector2f(3, 7));
}

void Ball::OnUpdate(const float& aDeltaTime)
{
	//calculate new pos
	sf::Vector2f tempNewPos = myShape.getPosition() + myDirection* myVelocity * aDeltaTime;

	//check if new pos is inside the screen
	if (tempNewPos.x< -(int)Window::CurrentWindow->GetRawWindow()->getSize().x / 2 && myDirection.x < 0)
	{
		myDirection.x *= -1;
	}
	if (tempNewPos.x +20 > Window::CurrentWindow->GetRawWindow()->getSize().x / 2 && myDirection.x > 0)
	{
		myDirection.x *= -1;
	}
	if (tempNewPos.y < -(int)Window::CurrentWindow->GetRawWindow()->getSize().y / 2 && myDirection.y < 0)
	{
		myDirection.y *= -1;
	}
	if (tempNewPos.y +20 > Window::CurrentWindow->GetRawWindow()->getSize().y / 2 && myDirection.y > 0)
	{
		myDirection.y *= -1;
	}

	//recalculate new pos
	myShape.setPosition(myShape.getPosition() + myDirection * myVelocity * aDeltaTime);
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
