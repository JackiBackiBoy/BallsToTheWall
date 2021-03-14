#include "TriangleEnemy.h"

TriangleEnemy::TriangleEnemy(const sf::Vector2f& aPosition, const float& aRotation) : Enemy(3, 15, aPosition, aRotation)
{
	myVelocity = 10.f;
	myAngle = Random::Float() * Math::Pi * 2;
	myDistance = 300 + (Random::Float() - 0.5f) * 50;
}

void TriangleEnemy::OnStart()
{
	Enemy::OnStart();
}

void TriangleEnemy::OnUpdate()
{
	myAngle += TimeTracker::GetDeltaTime();
	sf::Vector2f tempGoal = Player::GetPosition() + sf::Vector2f(cos(myAngle), sin(myAngle)) * (myDistance + sin(myAngle * 10) * 25);
	myShape.setRotation(Math::ToDegrees(atan2(Player::GetPosition().y - myShape.getPosition().y, Player::GetPosition().x - myShape.getPosition().x)));
	myShape.setPosition(Math::Lerp(myShape.getPosition(), tempGoal, 0.3f / Math::Distance(myShape.getPosition(), tempGoal) * TimeTracker::GetTimeScale()));
	Enemy::OnUpdate();
}

void TriangleEnemy::OnRender(sf::RenderWindow* aWindow)
{
	Enemy::OnRender(aWindow);
}
