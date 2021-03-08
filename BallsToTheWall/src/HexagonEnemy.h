#pragma once
#include "Enemy.h"
class HexagonEnemy : public Enemy
{
public:
	HexagonEnemy(const sf::Vector2f& aPosition, const float& aRotation);
	void OnStart() override;
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
};

