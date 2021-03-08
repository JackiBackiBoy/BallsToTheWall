#include "core/Window.h"
#include <iostream>
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
class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

	sf::Clock myClock;
	float myDeltaTime = 0;
	void OnStart() override
	{
		Random::RSeed();
		EnemyManager::OnStart();
		Ball::OnStart();
		Player::OnStart();
		Healthbar::OnStart();
		MusicManager::Start("EDM 2");
	}

	void OnUpdate() override
	{
		myDeltaTime = myClock.restart().asSeconds();
		TimeTracker::Update();
		EnemyManager::OnUpdate();
		Ball::OnUpdate();
		Player::OnUpdate();
		Healthbar::OnUpdate();
		MusicManager::OnUpdate();
	}

	void OnRender(sf::RenderWindow* aWindow) override
	{
		EnemyManager::OnRender(aWindow);
		Ball::OnRender(aWindow);
		Player::OnRender(aWindow);
		Healthbar::OnRender(aWindow);
	}
};

Window* BuildWindow()
{
	return new Sandbox("Balls To The Wall", 1240, 720);
}