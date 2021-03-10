#include "EnemyManager.h"
#include "Ball.h"
#include "Random.h"
#include "core\Window.h"
#include "Player.h"
std::vector<Enemy*> EnemyManager::myEnemies = std::vector<Enemy*>();
ParticleSystem EnemyManager::myParticleSystem = ParticleSystem(3000);
SummonSystem EnemyManager::mySummonSystem = SummonSystem();
bool* EnemyManager::OpenSectors = new bool[4] { true, true, true, true };

void EnemyManager::OnStart()
{

}

void EnemyManager::AddEnemyCopy(Enemy* anEnemy) 
{
	myEnemies.push_back(anEnemy);
}

void EnemyManager::OnUpdate()
{
	if (Ball::GetVelocity() != sf::Vector2f(0, 0))
	{
		for (auto& e : myEnemies)
		{
			e->OnUpdate();
		}
		for (auto it = myEnemies.begin(); it != myEnemies.end();)
		{
			
			if ((*it._Ptr)->IsDead()) // remove dead enemy and add death effect
			{
				ParticleProps tempPP = ParticleProps();
				tempPP.Position = sf::Vector2f((*it._Ptr)->GetPosition());
				tempPP.Velocity = (*it._Ptr)->GetVelocity();
				tempPP.VelocityVariation = sf::Vector2f(500, 500);
				tempPP.LifeTime = 10;

				tempPP.ColorBegin = sf::Color(200, 0, 0, 255);
				tempPP.ColorEnd = sf::Color::Transparent;

				tempPP.Shape = (*it._Ptr)->GetShape();
				tempPP.SizeBegin = { 0.3f, 0.3f };
				tempPP.SizeEnd = { 0.f, 0.f };
				tempPP.SizeVariation = { 0.1f, 0.1f };
				for (int i = 0; i < Random::Int(10, 30); i++)
				{
					myParticleSystem.Emit(tempPP);
				}
				delete (*it._Ptr);
				it = myEnemies.erase(it);
			}
			else ++it;
		}
		if (Random::Float() > 0.9995f) 
		{
			int tempPlayerSector;
			if (Player::GetPosition().x <= 0 && Player::GetPosition().y <= 0) 
			{
				tempPlayerSector = 0;
			}
			if (Player::GetPosition().x >= 0 && Player::GetPosition().y <= 0) 
			{ 
				tempPlayerSector = 1; 
			}
			if (Player::GetPosition().x <= 0 && Player::GetPosition().y >= 0)
			{
				tempPlayerSector = 2; 
			}
			if (Player::GetPosition().x >= 0 && Player::GetPosition().y >= 0)
			{
				tempPlayerSector = 3; 
			}
			std::vector<int> tempSectorIndices = std::vector<int>();
			for (int i = 0; i < 4; i++)
			{
				if (OpenSectors[i] && i != tempPlayerSector) 
				{
					tempSectorIndices.push_back(i);
				}
			}
			if (tempSectorIndices.size() != 0) 
			{
				int tempSector = tempSectorIndices[Random::Int(0, tempSectorIndices.size())];
				SummonProps tempSP = SummonProps();
				tempSP.CompTime = 5.f;
				tempSP.EnemyType = (EnemyType)Random::Int(0, 3);
				float tempW = Window::CurrentWindow->GetRawWindow()->getDefaultView().getSize().x / 2.f;
				float tempH = Window::CurrentWindow->GetRawWindow()->getDefaultView().getSize().y / 2.f;
				if (tempSector == 0) tempSP.Position = sf::Vector2f(-tempW, -tempH);
				if (tempSector == 1) tempSP.Position = sf::Vector2f(0, -tempH);
				if (tempSector == 2) tempSP.Position = sf::Vector2f(-tempW, 0);
				if (tempSector == 3) tempSP.Position = sf::Vector2f(0, 0);
				tempSP.Sector = &OpenSectors[tempSector];
				tempSP.Position += sf::Vector2f(
					std::min(std::max(Random::Float() * tempW, 50.f), tempW - 50),
					std::min(std::max(Random::Float() * tempH, 50.f), tempH - 50));
				mySummonSystem.Summon(tempSP);
			}
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
		for (auto& e : myEnemies)
		{
			e->OnRender(aWindow);
		}
	}
}
