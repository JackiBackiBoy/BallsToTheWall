#pragma once
#include "Enemy.h"
class SquareEnemy : public Enemy
{
public:
	SquareEnemy(const sf::Vector2f& aPosition, const float& aRotation);
	void OnStart() override;
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
};

