#include "TriangleEnemy.h"

TriangleEnemy::TriangleEnemy(const sf::Vector2f& aPosition, const float& aRotation) : Enemy(3, 15, aPosition, aRotation)
{
	myVelocity = 1.5f;

	myDistance = 300 + (Random::Float() - 0.5f) * 50;
}

void TriangleEnemy::OnStart()
{
	Enemy::OnStart();
	myAngle = atan2((GetPosition() - Player::GetPosition()).y, (GetPosition() - Player::GetPosition()).x) + (Random::Float() - 0.5f) * Math::Pi;
}

void TriangleEnemy::OnUpdate()
{
	myAngle += TimeTracker::GetDeltaTime() * !myStarting;
	sf::Vector2f tempGoal = Player::GetPosition() + sf::Vector2f(cos(myAngle), sin(myAngle)) * (myDistance + sin(myAngle * 10) * 25);
	myShape.setRotation(Math::ToDegrees(atan2(Player::GetPosition().y - myShape.getPosition().y, Player::GetPosition().x - myShape.getPosition().x)));
	myShape.setPosition(Math::Lerp(myShape.getPosition(), tempGoal, 200.f / Math::Distance(myShape.getPosition(), tempGoal) * TimeTracker::GetDeltaTime() * myVelocity));
	if (Math::Distance(myShape.getPosition(), tempGoal) < 1 && myStarting)
	{
		myStarting = false;
	}
	Enemy::OnUpdate();
}

void TriangleEnemy::OnRender(sf::RenderWindow* aWindow)
{
	Enemy::OnRender(aWindow);
}
