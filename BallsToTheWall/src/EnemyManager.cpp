#include "EnemyManager.h"
#include "Ball.h"
#include "Random.h"
#include "core\Window.h"
#include "Player.h"
std::vector<Enemy> EnemyManager::myEnemies = std::vector<Enemy>();
ParticleSystem EnemyManager::myParticleSystem = ParticleSystem(3000);
SummonSystem EnemyManager::mySummonSystem = SummonSystem();
void EnemyManager::OnStart()
{

}

void EnemyManager::AddEnemyCopy(Enemy anEnemy) 
{
	myEnemies.push_back(anEnemy);
}

void EnemyManager::OnUpdate()
{
	if (Ball::GetVelocity() != sf::Vector2f(0, 0))
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
		if (Random::Float() > 0.9995f) 
		{
			SummonProps tempSP = SummonProps();
			tempSP.CompTime = 5.f;
			tempSP.EnemyType = (EnemyType)Random::Int(0, 3);
			float tempRandomAngle = Random::Float() * 2 * Math::Pi;
			tempSP.Position = Player::GetPosition() + sf::Vector2f(
				cos(tempRandomAngle) * (200 + Random::Float() * Window::CurrentWindow->GetRawWindow()->getSize().x / 2.4f),
				sin(tempRandomAngle) * (200 + Random::Float() * Window::CurrentWindow->GetRawWindow()->getSize().y / 2.4f));
			tempSP.Position = sf::Vector2f(
				std::min(std::max(tempSP.Position.x, Window::CurrentWindow->GetRawWindow()->getSize().x / -2.4f), Window::CurrentWindow->GetRawWindow()->getSize().x / 2.4f),
				std::min(std::max(tempSP.Position.y, Window::CurrentWindow->GetRawWindow()->getSize().y / -2.4f), Window::CurrentWindow->GetRawWindow()->getSize().y / 2.4f));
			mySummonSystem.Summon(tempSP);
		}
		myParticleSystem.OnUpdate();
		mySummonSystem.OnUpdate();
	}
}

void EnemyManager::OnRender(sf::RenderWindow* aWindow)
{
	if (Ball::GetVelocity() != sf::Vector2f(0, 0)) 
	{
		myParticleSystem.OnRender(aWindow);
		mySummonSystem.OnRender(aWindow);
		for (Enemy& e : myEnemies)
		{
			e.OnRender(aWindow);
		}
	}
}
