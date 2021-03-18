#include "Sandbox.h"

float Sandbox::myMagnitude = 0;

Sandbox::Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

sf::Sprite TitleText;
sf::Texture TitleNameTex;

void OnStart()
{
	TitleNameTex.loadFromFile("Assets/GameName.png");
	TitleText = sf::Sprite(TitleNameTex);
	TitleText.setScale(sf::Vector2f(0.5f, 0.5f));
	TitleText.setPosition(sf::Vector2f(-(int)TitleNameTex.getSize().x * TitleText.getScale().x / 2, -(int)TitleNameTex.getSize().y * TitleText.getScale().y / 2));


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



void Sandbox::OnUpdate()
{
	TimeTracker::Update();
	EnemyManager::OnUpdate();
	Ball::OnUpdate();
	Player::OnUpdate();
	Healthbar::OnUpdate();
	MusicManager::OnUpdate();

	if (myMagnitude > 0)
	{
		myMagnitude -= fmin(myMagnitude * TimeTracker::GetDeltaTime() * 10, myMagnitude / 2);
	}
	GetRawWindow()->setView(sf::View(sf::Vector2f(Random::Int(-myMagnitude, myMagnitude + 1), Random::Int(-myMagnitude, myMagnitude + 1)), sf::Vector2f(myWidth, myHeight)));

}

void Sandbox::OnRender(sf::RenderWindow* aWindow)
{
	EnemyManager::OnRender(aWindow);
	Ball::OnRender(aWindow);
	Player::OnRender(aWindow);
	Healthbar::OnRender(aWindow);
}

void Sandbox::Shake(float aMagnitude)
{
	myMagnitude += aMagnitude;
}

Window* BuildWindow()
{
	return new Sandbox("Balls To The Wall", 1240, 720);
}