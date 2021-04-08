#include "HexagonEnemy.h"

HexagonEnemy::HexagonEnemy(const sf::Vector2f& aPosition, const float& aRotation) : Enemy(6, 20, aPosition, aRotation)
{
	myScore = 600;
}

void HexagonEnemy::OnStart()
{
	Enemy::OnStart();
}

void HexagonEnemy::OnUpdate()
{
	Enemy::OnUpdate();
}

void HexagonEnemy::OnRender(sf::RenderWindow* aWindow)
{
	Enemy::OnRender(aWindow);
}
