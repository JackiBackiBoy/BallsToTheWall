#include "core/Window.h"
#include <iostream>
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "math/Math.h"
#include "Healthbar.h"
#include "Player.h"
#include "Ball.h"
#include "TimeTracker.h"
class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

	sf::Clock myClock;
	float myDeltaTime = 0;

	void OnStart() override
	{
		Ball::OnStart();
		Player::OnStart();
		Healthbar::OnStart();
	}

	void OnUpdate() override
	{
		myDeltaTime = myClock.restart().asSeconds();
		TimeTracker::Update();

		Ball::OnUpdate();
		Player::OnUpdate();
		Healthbar::OnUpdate();
	}

	void OnRender(sf::RenderWindow* aWindow) override
	{
		Ball::OnRender(aWindow);
		Player::OnRender(aWindow);
		Healthbar::OnRender(aWindow);
	}
};

Window* BuildWindow()
{
	return new Sandbox("Balls To The Wall", 1240, 720);
}