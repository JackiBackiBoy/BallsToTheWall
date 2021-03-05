#include "core/Window.h"
#include <iostream>
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "math/Math.h"
#include "Player.h"
#include "Ball.h"

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
		myClock = sf::Clock();
		myClock.restart();
	}

	void OnUpdate() override
	{
		myDeltaTime = myClock.restart().asSeconds();

		Ball::OnUpdate(myDeltaTime);
		Player::OnUpdate(myDeltaTime);
	}

	void OnRender(sf::RenderWindow* aWindow) override
	{
		Ball::OnRender(aWindow);
		Player::OnRender(aWindow);
	}
};

Window* BuildWindow()
{
	return new Sandbox("Balls To The Wall", 1240, 720);
}