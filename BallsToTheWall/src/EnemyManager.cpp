#include "EnemyManager.h"
#include "Ball.h"
#include "Random.h"
std::vector<Enemy> EnemyManager::myEnemies = std::vector<Enemy>();
ParticleSystem EnemyManager::myParticleSystem = ParticleSystem(3000);
void EnemyManager::OnStart()
{
	myEnemies.push_back(Enemy(3, 20, sf::Vector2f(-50, -50)));
	myEnemies.push_back(Enemy(3, 20, sf::Vector2f(50, 50)));
}

void EnemyManager::OnUpdate()
{
	for (Enemy& e : myEnemies) 
	{
		e.OnUpdate();
	}
	for (auto it = myEnemies.begin(); it != myEnemies.end();) 
	{
		Enemy tempEnemy = *it._Ptr;
		if (tempEnemy.IsDead()) // remove dead enemy and add death effect
		{
			ParticleProps tempPP = ParticleProps();
			tempPP.Position = sf::Vector2f(tempEnemy.GetPosition());
			tempPP.Velocity = tempEnemy.GetVelocity();
			tempPP.VelocityVariation = sf::Vector2f(500, 500);
			tempPP.LifeTime = 10;

			tempPP.SizeBegin = 1000;
			tempPP.SizeEnd = 1;
			tempPP.SizeVariation = 100;

			tempPP.ColorBegin = sf::Color(200, 0, 0, 255);
			tempPP.ColorEnd = sf::Color::Transparent;
			for (int i = 0; i < Random::Int(10, 30); i++) 
			{
				myParticleSystem.Emit(tempPP);
			}
			myParticleSystem.Emit(tempPP);
			it = myEnemies.erase(it);
		}
		else ++it; 
	}
	myParticleSystem.OnUpdate();
}

void EnemyManager::OnRender(sf::RenderWindow* aWindow)
{
	myParticleSystem.OnRender(aWindow);
	for (Enemy& e : myEnemies)
	{
		e.OnRender(aWindow);
	}
}
