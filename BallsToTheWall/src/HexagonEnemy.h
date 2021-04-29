#pragma once
#include "Enemy.h"
class HexagonEnemy : public Enemy
{
public:
	HexagonEnemy(const sf::Vector2f& aPosition, const float& aRotation);
	void OnStart() override;
	void OnUpdate() override;
	void Die() override;
	void OnRender(sf::RenderWindow* aWindow) override;
private:
	int myHP = 2;
	float myTimeSinceHit = 1;
	float myLength;
	float myAngle;
	float myExtent = -Math::Pi / 2;
	float myAmplitude = 4;
	float myFrequency = 2;
};

