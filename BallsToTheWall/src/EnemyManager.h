#pragma once
#include <iostream>
#include <vector>
#include "ParticleSystem.h"
#include "SummonSystem.h"
class EnemyManager
{
public:
	static void OnStart();
	static void OnUpdate();
	static void OnRender(sf::RenderWindow* aWindow);
	static void AddEnemyCopy(Enemy* anEnemy);
private:
	static std::vector<Enemy*> myEnemies;
	static ParticleSystem myParticleSystem;
	static SummonSystem mySummonSystem;
	static bool* OpenSectors;
};

