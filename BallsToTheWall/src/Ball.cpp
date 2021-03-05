#include "Ball.h"

sf::CircleShape Ball::myShape = sf::CircleShape(10);

sf::Vector2f Ball::myDirection = sf::Vector2f(1,0);
float Ball::myVelocity = 0;

void Ball::OnStart()
{
	myShape.setPosition(sf::Vector2f(0, 0));
}

void Ball::OnUpdate(const float& aDeltaTime)
{
	myShape.setPosition(myShape.getPosition() + myDirection * myVelocity * aDeltaTime);
}

void Ball::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(myShape);
}
