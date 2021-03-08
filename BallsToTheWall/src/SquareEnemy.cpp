#include "SquareEnemy.h"

SquareEnemy::SquareEnemy(const sf::Vector2f& aPosition, const float& aRotation) : Enemy(4, 20, aPosition, aRotation)
{

}

void SquareEnemy::OnStart()
{
	Enemy::OnStart();
}

void SquareEnemy::OnUpdate()
{
	Enemy::OnUpdate();
}

void SquareEnemy::OnRender(sf::RenderWindow* aWindow)
{
	Enemy::OnRender(aWindow);
}
