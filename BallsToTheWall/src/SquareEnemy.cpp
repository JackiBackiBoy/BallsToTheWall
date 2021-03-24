#include "SquareEnemy.h"

SquareEnemy::SquareEnemy(const sf::Vector2f& aPosition, const float& aRotation) : Enemy(4, 20, aPosition, aRotation)
{
	myAxis = Random::Int(0, 2);
	if (myAxis) 
	{
		myExtent = (Random::Float() - 0.5f) * Window::GetSize().x * 0.9f;
		myTime = asin(aPosition.y / (Window::GetSize().y * 0.4f));
	}
	else 
	{
		myExtent = (Random::Float() - 0.5f) * Window::GetSize().y * 0.9f;
		myTime = asin(aPosition.x / (Window::GetSize().x * 0.45f));
	}
	myTime = Random::Float() * Math::Pi;
	mySpeed = (1 + Random::Float() * 0.5f);
}

void SquareEnemy::OnStart()
{
	Enemy::OnStart();
}

void SquareEnemy::OnUpdate()
{
	myTime += TimeTracker::GetDeltaTime() * mySpeed * (!myStarting);
	sf::Vector2f tempGoal = sf::Vector2f(
		(myAxis) * myExtent + (!myAxis) * sin(myTime) * Window::GetSize().x * 0.45f,
		(!myAxis) * myExtent + (myAxis) * sin(myTime) * Window::GetSize().y * 0.4f);
	myShape.setPosition(Math::Lerp(myShape.getPosition(), tempGoal, 0.3f / Math::Distance(myShape.getPosition(), tempGoal) * TimeTracker::GetTimeScale()));
	if (Math::Distance(myShape.getPosition(), tempGoal) < 1) 
	{
		myStarting = false;
	}
	Enemy::OnUpdate();
}

void SquareEnemy::OnRender(sf::RenderWindow* aWindow)
{
	Enemy::OnRender(aWindow);
}
