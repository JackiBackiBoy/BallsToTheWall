#include "Sandbox.h"

float Sandbox::myMagnitude = 0;

Sandbox::Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

sf::Sprite TitleText;
sf::Texture TitleNameTex;
bool GameStarted = false;
int myStartWidth, myStartHeight;

int myTitleSplit = 10;

ParticleSystem myTitleParticleSystem;

void Sandbox::OnStart()
{
	myStartWidth = myWidth;
	myStartHeight = myHeight;

	TitleNameTex.loadFromFile("Assets/GameName.png");
	TitleText = sf::Sprite(TitleNameTex);
	TitleText.setScale(sf::Vector2f(0.5f, 0.5f));
	TitleText.setPosition(sf::Vector2f(-(int)TitleNameTex.getSize().x * TitleText.getScale().x / 2, -(int)TitleNameTex.getSize().y * TitleText.getScale().y / 2));


	myTitleParticleSystem = ParticleSystem(TitleNameTex.getSize().x / myTitleSplit * TitleNameTex.getSize().y / myTitleSplit);

	Options::Load();

	Random::RSeed();
	EnemyManager::OnStart();
	Ball::OnStart();
	Player::OnStart();
	Healthbar::OnStart();
	MusicManager::Start("EDM 2");

	Player::SetPosition(sf::Vector2f(0, 65));
	Mouse::SetPosition(sf::Vector2i(0, 20));
	myHeight /= 2;
	myWidth /= 2;
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

	if ((std::abs(Ball::GetVelocity().x) > 0 || std::abs(Ball::GetVelocity().y > 0)) && !GameStarted)
	{
		GameStarted = true;
		sf::Image tempImg = TitleNameTex.copyToImage();
		for (int i = 0; i < myTitleParticleSystem.GetSize(); i++)
		{
			int tempPlace = i * myTitleSplit / TitleNameTex.getSize().x;
			sf::Color tempCol = tempImg.getPixel(tempPlace % tempImg.getSize().x, tempPlace / tempImg.getSize().x);
			ParticleProps tempProp = ParticleProps();
			tempProp.ColorBegin = tempCol;
			tempProp.ColorEnd = sf::Color::Transparent;

			tempProp.Position = TitleText.getPosition() + sf::Vector2f(tempPlace % tempImg.getSize().x, tempPlace / tempImg.getSize().x);
			myTitleParticleSystem.Emit(tempProp);
		}
	}
	if (GameStarted && (myWidth != myStartWidth || myHeight != myStartHeight))
	{
		myWidth = ceil(Math::Lerp(myWidth, myStartWidth, 10.f * TimeTracker::GetDeltaTime()));
		myHeight = myStartHeight * myWidth / myStartWidth;
	}



}

void Sandbox::OnRender(sf::RenderWindow* aWindow)
{
	if (!GameStarted)
		aWindow->draw(TitleText);
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