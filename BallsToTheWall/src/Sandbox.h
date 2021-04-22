#pragma once
#include <iostream>
#include "core/Window.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "math/Math.h"
#include "Healthbar.h"
#include "Player.h"
#include "Ball.h"
#include "TimeTracker.h"
#include "EnemyManager.h"
#include "Random.h"
#include "MusicManager.h"
#include "SaveLoad.h"
#include "Options.h"
struct Score
{
	std::string Name;
	int Value;
	Score()
	{
		Name = "";
		Value = 0;
	}
	Score(std::string aName, int aValue)
	{
		Name = aName;
		Value = aValue;
	}
};
class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight);

	void OnStart() override;

	void OnUpdate() override;

	void OnRender(sf::RenderWindow* aWindow) override;

	static void Shake(float aMagnitude);
private:
	static float myMagnitude;

	void CheckScore(Score aScore);
};