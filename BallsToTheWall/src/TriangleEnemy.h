#pragma once
#include "Enemy.h"
class TriangleEnemy : public Enemy
{
public:
	TriangleEnemy(const sf::Vector2f& aPosition, const float& aRotation);
	void OnStart() override;
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
private:
	float myAngle = 0;
	float myDistance = 300;
};

