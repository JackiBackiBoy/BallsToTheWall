#include "TriangleEnemy.h"

TriangleEnemy::TriangleEnemy(const sf::Vector2f& aPosition, const float& aRotation) : Enemy(3, 15, aPosition, aRotation)
{

}

void TriangleEnemy::OnStart()
{
	Enemy::OnStart();
}

void TriangleEnemy::OnUpdate()
{
	Enemy::OnUpdate();
}

void TriangleEnemy::OnRender(sf::RenderWindow* aWindow)
{
	Enemy::OnRender(aWindow);
}
