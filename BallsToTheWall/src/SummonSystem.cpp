#include "SummonSystem.h"
#include "TimeTracker.h"
#include "Random.h"
#include "math\Math.h"
#include "EnemyManager.h"

SummonSystem::SummonSystem(unsigned int aSummonCount)
{
	mySummons.resize(aSummonCount);
}
void SummonSystem::OnUpdate()
{
	for (auto& s : mySummons)
	{
		if (!s.Active) continue;

		s.Remaining -= TimeTracker::GetDeltaTime();
		if (s.Remaining <= 0.0f)
		{
			s.Active = false;
			for (auto it = s.Enemies.begin(); it != s.Enemies.end();) 
			{
				EnemyManager::AddEnemyCopy(*it._Ptr);
				it = s.Enemies.erase(it);
				s.EndPositions.erase(s.EndPositions.begin() + (it - s.Enemies.begin()));
			}
			continue;
		}

		float tempTime = s.Remaining / s.CompTime;
		for (int i = 0; i < s.Enemies.size(); i++) 
		{
			s.Enemies[i].SetPosition(Math::Lerp(s.EndPositions[i], sf::Vector2f(0, 0), tempTime) + s.Position);
			s.Enemies[i].SetScale(sf::Vector2f(1 - tempTime, 1 - tempTime));
			s.Enemies[i].Collision();
		}
		for (auto it = s.Enemies.begin(); it != s.Enemies.end();) 
		{
			if (it._Ptr->IsDead()) 
			{
				EnemyManager::AddEnemyCopy(*it._Ptr);
				it = s.Enemies.erase(it);
				s.EndPositions.erase(s.EndPositions.begin() + (it - s.Enemies.begin()));
			}
			else it++;
		}
	}
}

void SummonSystem::OnRender(sf::RenderWindow* aWindow)
{
	for (auto& s : mySummons)
	{
		if (!s.Active) continue;


		for (int i = 0; i < s.Enemies.size(); i++) 
		{
			s.Enemies[i].OnRender(aWindow);
		}
	}
}

void SummonSystem::Summon(const SummonProps& someSummonProps) 
{
	SummonData& tempS = mySummons[mySummonIndex];
	tempS.Active = true;
	tempS.Position = someSummonProps.Position;
	tempS.CompTime = someSummonProps.CompTime;
	tempS.Remaining = someSummonProps.CompTime;
	if (someSummonProps.EnemyType == EnemyType::Triangle) 
	{
		TriangleEnemy tempEnemy = TriangleEnemy(someSummonProps.Position, 0);
		float tempR = Math::Length(tempEnemy.GetShape().getPoint(0));
		float tempH = tempR * 0.5f;
		float tempW = tempR * sqrt(3) / 2;
		tempS.Enemies.push_back(TriangleEnemy({ 0, 0 }, Math::Pi / 2.f));
		tempS.EndPositions.push_back(sf::Vector2f(0, tempH));

		tempS.Enemies.push_back(TriangleEnemy({ 0, 0 }, Math::Pi / 2.f));
		tempS.EndPositions.push_back(sf::Vector2f(-tempW, -tempR));

		tempS.Enemies.push_back(TriangleEnemy({ 0, 0 }, -Math::Pi / 2.f));
		tempS.EndPositions.push_back(sf::Vector2f(0, -tempH));

		tempS.Enemies.push_back(TriangleEnemy({ 0, 0 }, Math::Pi / 2.f));
		tempS.EndPositions.push_back(sf::Vector2f(tempW, -tempR));
	}
	

	if (mySummonIndex == 0) 
	{
		mySummonIndex = mySummons.size() - 1;
	}
	else mySummonIndex--;
}