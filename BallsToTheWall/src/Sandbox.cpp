#include "Sandbox.h"

float Sandbox::myMagnitude = 0;

Sandbox::Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

sf::Sprite TitleText;
sf::Texture TitleNameTex;
bool GameStarted = false;
int myStartWidth, myStartHeight;
float myTempWidth;

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
	myTitleParticleSystem = ParticleSystem((TitleNameTex.getSize().x / myTitleSplit) * (TitleNameTex.getSize().y/myTitleSplit));

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
	myTempWidth = myWidth;
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
		Shake(200);
		sf::Image tempImg = TitleNameTex.copyToImage();
		for (int i = 0; i < myTitleParticleSystem.GetSize(); i++)
		{
			int tempPlace = i *   myTitleSplit;
			sf::Color tempCol = tempImg.getPixel(tempPlace % tempImg.getSize().x,  myTitleSplit*(tempPlace / tempImg.getSize().x));
			ParticleProps tempProp = ParticleProps();
			if (tempCol == sf::Color::Transparent)
			{
				continue;
			}
			tempProp.ColorBegin = tempCol;
			tempProp.SizeEnd = sf::Vector2f(0,0);
			tempProp.LifeTime = 3;
			tempProp.Position = TitleText.getPosition() + sf::Vector2f(tempPlace % tempImg.getSize().x * TitleText.getScale().x, (myTitleSplit * tempPlace / tempImg.getSize().x) * TitleText.getScale().x);
			tempProp.PointCount = Random::Int(3, 7);
			tempProp.Velocity = tempProp.Position * 5.f;
			tempProp.VelocityVariation = sf::Vector2f(70, 70);
			tempProp.AngVelVariation = 30;
			myTitleParticleSystem.Emit(tempProp);
		}
	}
	myTitleParticleSystem.OnUpdate();
	if (GameStarted && (myWidth <= myStartWidth || myHeight <= myStartHeight))
	{
		myTempWidth = Math::Lerp(myTempWidth, myStartWidth, 7.f * TimeTracker::GetDeltaTime());
		myWidth = (int)myTempWidth;
		if (myWidth > myStartWidth)
			myWidth = myStartWidth;
		myHeight = myStartHeight * myWidth / myStartWidth;
	}



}

void Sandbox::OnRender(sf::RenderWindow* aWindow)
{
	if (!GameStarted)
		aWindow->draw(TitleText);
	myTitleParticleSystem.OnRender(aWindow);
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