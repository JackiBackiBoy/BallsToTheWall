#include "Ball.h"
#include "core/Window.h"
#include "math/Math.h"
#include <Player.h>
#include "TimeTracker.h"

sf::CircleShape Ball::myShape = sf::CircleShape(10);

sf::Vector2f Ball::myDirection = sf::Vector2f(0, 0);
float Ball::myVelocity = 0;

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

sf::Vector2f Ball::GetVelocity()
{
	return myDirection * myVelocity;
}

sf::CircleShape Ball::GetShape()
{
	return myShape;
}

bool CheckLineCircle(const sf::Vector2f& circle, const float& radius, const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	sf::Vector2f v1 = {};
	sf::Vector2f v2 = {};
	sf::Vector2f v3 = {};
	float u;
	// get dist to end of line
	v2.x = circle.x - p1.x;
	v2.y = circle.y - p1.y;
	// check if end points are inside the circle
	if (std::min(Math::Length(p2 - circle), Math::Length(v2)) <= radius)
	{
		return true;
	}
	// get the line as a vector
	v1.x = p2.x - p1.x;
	v1.y = p2.y - p1.y;
	// get the unit distance of the closest point on the line
	u = (v2.x * v1.x + v2.y * v1.y) / (v1.y * v1.y + v1.x * v1.x);
	// is this on the line segment
	if (u >= 0 && u <= 1) {
		v3.x = v1.x * u;  // get the point on the line segment
		v3.y = v1.y * u;
		// get the distance to that point and return true or false depending on the 
		// it being inside the circle
		return (Math::Length(v3 - v2) <= radius);
	}
	return false; // no intercept
}

bool Ball::Intersects(const sf::ConvexShape& aPolygon)
{
	auto current = aPolygon.getPoint(0);
	current.x *= aPolygon.getScale().x;
	current.y *= aPolygon.getScale().y;
	current = Math::RotPDeg(current, aPolygon.getRotation());
	for (auto i = 0; i < aPolygon.getPointCount(); i++)
	{
		auto next = aPolygon.getPoint((i + 1) % aPolygon.getPointCount());
	    next.x *= aPolygon.getScale().x;
		next.y *= aPolygon.getScale().y;
		next = Math::RotPDeg(next, aPolygon.getRotation());
		if (CheckLineCircle(myShape.getPosition(), myShape.getRadius(), current + aPolygon.getPosition(), next + aPolygon.getPosition()))
		{
			//slows ball down (tweaking needed)
			myVelocity *= 0.97f;
			return true;
		}
		current = next;
	}
	return false;
}
