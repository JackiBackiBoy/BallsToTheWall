#include "EnemyManager.h"
#include "Ball.h"
#include "Random.h"
#include "Sandbox.h"
#include "Player.h"
std::vector<Enemy*> EnemyManager::myEnemies = std::vector<Enemy*>();
ParticleSystem EnemyManager::myParticleSystem = ParticleSystem(3000);
SummonSystem EnemyManager::mySummonSystem = SummonSystem();
bool* EnemyManager::myOpenSectors = new bool[4] { true, true, true, true };
float EnemyManager::mySummonTime = 2;
float EnemyManager::myCurrentSummonTime = 0;
std::vector<ScoreText> EnemyManager::myTexts = std::vector<ScoreText>();
int EnemyManager::myCurrentSummonLevel = 1;
std::vector<sf::Color> EnemyManager::myParticleColors = std::vector<sf::Color>();
sf::Texture EnemyManager::myTexture = sf::Texture();



void EnemyManager::OnStart()
{
	
}

void EnemyManager::AddEnemyCopy(Enemy* anEnemy) 
{
	myEnemies.push_back(anEnemy);
	anEnemy->OnStart();
}

void EnemyManager::IncreaseSummonLevel()
{
	myCurrentSummonLevel++;
}

void EnemyManager::Reset()
{
	myCurrentSummonLevel = 1;
	myEnemies.clear();
	myParticleSystem = ParticleSystem(3000);
	mySummonSystem = SummonSystem();
	myCurrentSummonTime = 0;
	myTexts.clear();
	myOpenSectors = new bool[4]{ true, true, true, true };
	if (myTexture.loadFromFile("Assets/"+ Sandbox::GetPack() + "Enemy.png"))
	{
		sf::Image tempImg = myTexture.copyToImage();
		int step = tempImg.getSize().y / 32;
		for (int i = 0; i < 32; i++)
		{
			myParticleColors.push_back(tempImg.getPixel(tempImg.getSize().x / 2, step * i));
		}
	}
	else
	{
		myParticleColors.push_back(sf::Color(200, 0, 0));
	}
}

sf::Texture& EnemyManager::GetEnemyTexture()
{
	return myTexture;
}

void EnemyManager::OnUpdate()
{

	if (Player::GetScore() > 4000 && myCurrentSummonLevel == 1)
	{
		IncreaseSummonLevel();
	}
	if (Player::GetScore() > 10000 && myCurrentSummonLevel == 2)
	{
		IncreaseSummonLevel();
	}
	if (Ball::GetVelocity() != sf::Vector2f(0, 0))
	{
		for (auto& e : myEnemies)
		{
			e->OnUpdate();
		}
		for (auto it = myEnemies.begin(); it != myEnemies.end();)
		{
			
			if ((*it)->IsDead()) // remove dead enemy and add particle effect
			{
				ParticleProps tempPP = ParticleProps();
				tempPP.Position = sf::Vector2f((*it._Ptr)->GetPosition());
				tempPP.Velocity = (*it._Ptr)->GetVelocity();
				tempPP.VelocityVariation = sf::Vector2f(500, 500);
				tempPP.LifeTime = 5;

				tempPP.ColorEnd = sf::Color::Transparent;

				tempPP.Shape = (*it._Ptr)->GetShape();
				tempPP.SizeBegin = { 0.3f, 0.3f };
				tempPP.SizeEnd = { 0.f, 0.f };
				tempPP.SizeVariation = { 0.1f, 0.1f };

				for (int i = 0; i < Random::Int(10, 30); i++)
				{
					tempPP.ColorBegin = myParticleColors[Random::Int(0, myParticleColors.size())];
					myParticleSystem.Emit(tempPP);
				}
				ScoreText tempText = ScoreText();
				tempText.Init();
				tempText.Text = sf::Text(std::to_string((*it._Ptr)->GetScore()), Player::GetScoreFont());
				tempText.Text.setPosition((*it._Ptr)->GetPosition() - sf::Vector2f(tempText.Text.getLocalBounds().width/2, tempText.Text.getLocalBounds().height/2));

				Player::AddScore((*it._Ptr)->GetScore());
				for (int i = 0; i < myTexts.size(); i++)
				{
					if (Math::Distance(tempText.Text.getPosition(), myTexts[i].Text.getPosition())< 100)
					{ 
						
						int val = std::stoi((std::string)tempText.Text.getString()) + std::stoi((std::string)myTexts[i].Text.getString());
						tempText.Text.setString(std::to_string(val));
						tempText.AddSize(5);

						tempText.Text.setPosition((tempText.Text.getPosition() + myTexts[i].Text.getPosition()) / 2.f);

						myTexts.erase(myTexts.begin() + i);
						break;
					}
				}

				myTexts.push_back(tempText);

				delete (*it._Ptr);
				it = myEnemies.erase(it);
				Sandbox::Shake(10);
			}
			else
			{
				it++;
			}
		}

		myCurrentSummonTime += TimeTracker::GetDeltaTime();
		if (myCurrentSummonTime >= mySummonTime) 
		{
			int tempPlayerSector;
			if (Player::GetPosition().x <= 0 && Player::GetPosition().y <= 0) 
			{
				tempPlayerSector = 0;
			}
			if (Player::GetPosition().x >= 0 && Player::GetPosition().y <= 0) 
			{ 
				tempPlayerSector = 1; 
			}
			if (Player::GetPosition().x <= 0 && Player::GetPosition().y >= 0)
			{
				tempPlayerSector = 2; 
			}
			if (Player::GetPosition().x >= 0 && Player::GetPosition().y >= 0)
			{
				tempPlayerSector = 3; 
			}
			std::vector<int> tempSectorIndices = std::vector<int>();
			for (int i = 0; i < 4; i++)
			{
				if (myOpenSectors[i] && i != tempPlayerSector) 
				{
					tempSectorIndices.push_back(i);
				}
			}
			if (tempSectorIndices.size() != 0) 
			{
				int tempSector = tempSectorIndices[Random::Int(0, tempSectorIndices.size())];
				SummonProps tempSP = SummonProps();
				tempSP.EnemyType = (EnemyType)Random::Int(0, myCurrentSummonLevel);
				float tempW = Window::GetSize().x / 2.f;
				float tempH = Window::GetSize().y / 2.f;
				if (tempSector == 0) tempSP.Position = sf::Vector2f(-tempW, -tempH);
				if (tempSector == 1) tempSP.Position = sf::Vector2f(0, -tempH);
				if (tempSector == 2) tempSP.Position = sf::Vector2f(-tempW, 0);
				if (tempSector == 3) tempSP.Position = sf::Vector2f(0, 0);
				tempSP.Sector = &myOpenSectors[tempSector];
				tempSP.Position += sf::Vector2f(
					std::min(std::max(Random::Float() * tempW, 50.f), tempW - 50),
					std::min(std::max(Random::Float() * tempH, 50.f), tempH - 50));
				mySummonSystem.Summon(tempSP);
				myCurrentSummonTime = Random::Float() * -3 - myEnemies.size() * 0.2f;
			}
			tempSectorIndices.clear();
		}
	}
	myParticleSystem.OnUpdate();
	mySummonSystem.OnUpdate();
}


void EnemyManager::OnRender(sf::RenderWindow* aWindow)
{
	for (int i = 0; i < myTexts.size(); i++)
	{
		myTexts[i].DecreaseAlpha(TimeTracker::GetDeltaTime() * 255 / myTexts[i].FadeTime);
		myTexts[i].Text.setPosition(myTexts[i].Text.getPosition() + sf::Vector2f(0, -TimeTracker::GetDeltaTime() * 50));
		myTexts[i].UpdateRainbow();

		aWindow->draw(myTexts[i].Text);
	}
	while (myTexts.size() > 0 && myTexts[0].Alpha <= 0)
	{
		myTexts.erase(myTexts.begin());
	}
	if (Ball::GetVelocity() != sf::Vector2f(0, 0)) 
	{
		myParticleSystem.OnRender(aWindow);
		mySummonSystem.OnRender(aWindow);
		for (auto& e : myEnemies)
		{
			e->OnRender(aWindow);
		}
	}

}
