#pragma once
#include <iostream>
#include <vector>
#include "Enemy.h"
#include "ParticleSystem.h"
class EnemyManager
{
public:
	static void OnStart();
	static void OnUpdate();
	static void OnRender(sf::RenderWindow* aWindow);
private:
	static std::vector<Enemy> myEnemies;
	static ParticleSystem myParticleSystem;
};

