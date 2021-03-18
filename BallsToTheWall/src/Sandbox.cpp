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
#include "SaveLoad.h"
#include "Options.h"
class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};
	sf::Sprite TitleText;

	sf::Texture TitleNameTex;
	sf::Clock myClock;
	float myDeltaTime = 0;
	void OnStart() override
	{
		TitleNameTex.loadFromFile("Assets/GameName.png");
		TitleText = sf::Sprite(TitleNameTex);
		TitleText.setScale(sf::Vector2f(0.5f,0.5f));
		TitleText.setPosition(sf::Vector2f(-(int)TitleNameTex.getSize().x*TitleText.getScale().x/2, -(int)TitleNameTex.getSize().y * TitleText.getScale().y /2));

		Options::Load();

		Random::RSeed();
		EnemyManager::OnStart();
		Ball::OnStart();
		Player::OnStart();
		Healthbar::OnStart();
		MusicManager::Start("EDM 2");

		Player::SetPosition(sf::Vector2f(0, 65));
		sf::Mouse::setPosition(sf::Vector2i(0, 60));
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
		aWindow->draw(TitleText);
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