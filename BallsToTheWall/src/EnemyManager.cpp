#include "EnemyManager.h"
#include "Ball.h"
#include "Random.h"
std::vector<Enemy> EnemyManager::myEnemies = std::vector<Enemy>();
ParticleSystem EnemyManager::myParticleSystem = ParticleSystem(3000);
SummonSystem EnemyManager::mySummonSystem = SummonSystem();
void EnemyManager::OnStart()
{
	SummonProps tempSP = SummonProps();
	tempSP.CompTime = 10.f;
	tempSP.Color = sf::Color(200, 0, 0, 255);
	tempSP.EnemyType = EnemyType::Hexagon;
	tempSP.Position = sf::Vector2f(170, -100);
	mySummonSystem.Summon(tempSP);
}

void EnemyManager::AddEnemyCopy(Enemy anEnemy) 
{
	myEnemies.push_back(anEnemy);
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

			tempPP.ColorBegin = sf::Color(200, 0, 0, 255);
			tempPP.ColorEnd = sf::Color::Transparent;

			tempPP.Shape = tempEnemy.GetShape();
			tempPP.SizeBegin = { 0.3f, 0.3f };
			tempPP.SizeEnd = { 0.f, 0.f };
			tempPP.SizeVariation = { 0.1f, 0.1f };
			for (int i = 0; i < Random::Int(10, 30); i++) 
			{
				myParticleSystem.Emit(tempPP);
			}
			it = myEnemies.erase(it);
		}
		else ++it; 
	}
	myParticleSystem.OnUpdate();
	mySummonSystem.OnUpdate();
}

void EnemyManager::OnRender(sf::RenderWindow* aWindow)
{
	myParticleSystem.OnRender(aWindow);
	mySummonSystem.OnRender(aWindow);
	for (Enemy& e : myEnemies)
	{
		e.OnRender(aWindow);
	}
}
