#include "SquareEnemy.h"

SquareEnemy::SquareEnemy(const sf::Vector2f& aPosition, const float& aRotation) : Enemy(4, 20, aPosition, aRotation)
{
	myX = (Random::Float() - 0.5f) * Window::GetSize().x * 0.9f;
	myTime = Random::Float() * Math::Pi;
	mySpeed = (1 + Random::Float() * 0.5f);
}

void SquareEnemy::OnStart()
{
	Enemy::OnStart();
}

void SquareEnemy::OnUpdate()
{
	myTime += TimeTracker::GetDeltaTime() * mySpeed;
	sf::Vector2f tempGoal = sf::Vector2f(myX, sin(myTime) * Window::GetSize().y * 0.4f);
	myShape.setPosition(Math::Lerp(myShape.getPosition(), tempGoal, 0.3f / Math::Distance(myShape.getPosition(), tempGoal) * TimeTracker::GetTimeScale()));
	Enemy::OnUpdate();
}

void SquareEnemy::OnRender(sf::RenderWindow* aWindow)
{
	Enemy::OnRender(aWindow);
}
