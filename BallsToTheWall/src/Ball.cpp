#include "Ball.h"
#include "core/Window.h"
#include "math/Math.h"
#include <Player.h>
#include "TimeTracker.h"
#include "Sandbox.h"
sf::CircleShape Ball::myShape = sf::CircleShape(13);
sf::Texture Ball::myTexture = sf::Texture();
sf::Vector2f Ball::myDirection = sf::Vector2f(0, 0);
float Ball::myVelocity = 0;

void Ball::OnStart()
{
	myShape.setRadius(myShape.getRadius() * Sandbox::GetScaleFactor());
	myShape.setPosition(sf::Vector2f(-45, 0) * Sandbox::GetScaleFactor());
	myShape.setOrigin(sf::Vector2f(myShape.getLocalBounds().width / 2, myShape.getLocalBounds().height / 2));
	myDirection = Math::Normalized(sf::Vector2f(3, 7));
	//myShape.setFillColor(sf::Color(200, 255, 255));
	myShape.setFillColor(sf::Color(255, 255, 255, 255));
	myTexture.loadFromFile("Assets/NameGoesHere.png");
	myShape.setTexture(&myTexture);
}

void Ball::OnUpdate()
{
	//calculate new pos
	sf::Vector2f tempNewPos = myShape.getPosition() + myDirection * myVelocity * TimeTracker::GetDeltaTime();

	//check if new pos is inside the screen
	if (tempNewPos.x < -(int)Window::GetSize().x / 2 && myDirection.x < 0)
	{
		myDirection.x *= -1;
	}
	if (tempNewPos.x + 20 > Window::GetSize().x / 2 && myDirection.x > 0)
	{
		myDirection.x *= -1;
	}
	if (tempNewPos.y < -(int)Window::GetSize().y / 2 && myDirection.y < 0)
	{
		myDirection.y *= -1;
	}
	if (tempNewPos.y + 20 > Window::GetSize().y / 2 && myDirection.y > 0)
	{
		myDirection.y *= -1;
	}

	//recalculate new pos
	myShape.setPosition(myShape.getPosition() + myDirection * myVelocity * TimeTracker::GetDeltaTime());
}

void Ball::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(myShape);
}

sf::Vector2f Ball::GetPosition()
{
	return myShape.getPosition();
}

void Ball::Hit(const float& anAngle)
{
	myDirection = sf::Vector2f(std::cos(anAngle), std::sin(anAngle));
	if (myVelocity == 0)
		myVelocity += 400;
	else if (myVelocity < 1000)
		myVelocity += 100;
	else if (myVelocity < 1500)
		myVelocity += 75;
	else
		myVelocity += 50;
}

void Ball::SetDirection(const sf::Vector2f& aVector)
{
	myDirection = aVector;
}

sf::Vector2f Ball::GetVelocity()
{
	return myDirection * myVelocity;
}

sf::CircleShape Ball::GetShape()
{
	return myShape;
}

bool CheckLineCircle(const sf::Vector2f& circle, const float& radiusSqrd, const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	// get dist to end of line
	sf::Vector2f v2 = circle - p1;
	// check if end points are inside the circle
	if (std::min(Math::LengthSqrd(p2 - circle), Math::LengthSqrd(v2)) <= radiusSqrd)
	{
		return true;
	}
	// get the line as a vector
	sf::Vector2f v1 = p2 - p1;
	// get the unit distance of the closest point on the line
	float u = (v2.x * v1.x + v2.y * v1.y) / (v1.y * v1.y + v1.x * v1.x);
	// if this is on the line segment
	if (u >= 0 && u <= 1) 
	{
		// get the point on the line segment
		sf::Vector2f v3 = v1 * u; 

		// get the distance to that point and return true or false depending on the 
		// it being inside the circle
		return (Math::LengthSqrd(v3 - v2) <= radiusSqrd);
	}
	return false; // no intercept
}

bool Ball::Intersects(const sf::ConvexShape& aPolygon)
{
	auto current = aPolygon.getPoint(aPolygon.getPointCount() - 1);
	current.x *= aPolygon.getScale().x;
	current.y *= aPolygon.getScale().y;
	current = Math::RotPDeg(current, aPolygon.getRotation());
	float tempRadiusSqrd = myShape.getRadius() * myShape.getRadius();
	for (auto i = 0; i < aPolygon.getPointCount(); i++)
	{
		auto next = aPolygon.getPoint(i);
	    next.x *= aPolygon.getScale().x;
		next.y *= aPolygon.getScale().y;
		next = Math::RotPDeg(next, aPolygon.getRotation());
		if (CheckLineCircle(myShape.getPosition(),  tempRadiusSqrd, current + aPolygon.getPosition(), next + aPolygon.getPosition()))
		{
			//If ball hits enemy, reduce the velocity of the ball
			if (aPolygon.getPointCount() != 6)
			{
				myVelocity *= 0.96f;
			}
			return true;
		}
		current = next;
	}
	return false;
}

void Ball::Reset()
{
	myShape.setPosition(sf::Vector2f(-45, 0));
	myDirection = sf::Vector2f(0, 0);
	myVelocity = 0;
}
