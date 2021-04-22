#pragma once
#include <iostream>
#include <vector>
#include "ParticleSystem.h"
#include "SummonSystem.h"

struct ScoreText
{
	float Alpha = 255;
	sf::Text Text;
	float RainbowOffset = 0;
	int Size = 30;
	float FadeTime = 3.14159f;
	void Init()
	{
		RainbowOffset = 100 * Random::Float();
	}
	void DecreaseAlpha(float aValue)
	{
		Alpha -= aValue;
		Text.setFillColor(sf::Color(Text.getFillColor().r, Text.getFillColor().g, Text.getFillColor().b, Alpha));
	}
	void UpdateRainbow()
	{
		Text.setFillColor(Math::ShiftRainbow(Text.getFillColor(), TimeTracker::GetDeltaTime() * (500+ RainbowOffset)));
	}
	void AddSize(int aValue)
	{
		Size += aValue;
		Text.setCharacterSize(Size);
	}
};

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
	static bool* myOpenSectors;
	static float mySummonTime;
	static float myCurrentSummonTime;
	static std::vector<ScoreText> myTexts;
};

