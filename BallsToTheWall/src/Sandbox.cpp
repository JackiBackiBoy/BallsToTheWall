#include "Sandbox.h"
#include"InputManager.h"
#include "Button.h"

float Sandbox::myMagnitude = 0;
Score myHighscores[10];

Sandbox::Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

sf::Sprite TitleText;
sf::Texture TitleNameTex;
bool GameStarted = false;
int myStartWidth, myStartHeight;
float myTempWidth;
bool myScoreCheckedFlag = false;

sf::Text myPlayerText;
sf::Text myGameOverText;
int myTitleSplit = 10;
std::string myPlayerInput;

Button myRestartButton;
Button myShopButton;

ParticleSystem myTitleParticleSystem;


Button myGameButton;
std::vector<Button> myTexButtons;
enum TexturePack
{
	None,
	DotCom,
	Lul,
	Fun,
	Inception
};

enum GameState
{
	Game,
	Options,
	Shop
};

GameState myGameState = Game;


void Sandbox::OnStart()
{
	for (int i = 0; i < 10; i++)
	{
		std::string tempValue = SaveLoad::Load("HSV" + std::to_string(i));
		std::string tempName = SaveLoad::Load("HSN" + std::to_string(i));
		myHighscores[i] = Score(tempName != "" ? tempName : " ", std::stoi(tempValue != "" ? tempValue : "0"));
	}

	myStartWidth = myWidth;
	myStartHeight = myHeight;

	TitleNameTex.loadFromFile("Assets/GameName.png");
	TitleText = sf::Sprite(TitleNameTex);
	TitleText.setScale(sf::Vector2f(0.5f, 0.5f));
	TitleText.setPosition(sf::Vector2f(-(int)TitleNameTex.getSize().x * TitleText.getScale().x / 2, -(int)TitleNameTex.getSize().y * TitleText.getScale().y / 2));
	myTitleParticleSystem = ParticleSystem((TitleNameTex.getSize().x / myTitleSplit) * (TitleNameTex.getSize().y / myTitleSplit));

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

	myPlayerText = sf::Text("", Player::GetScoreFont(), 50);
	myGameOverText = sf::Text("GAME OVER", Player::GetScoreFont(), 100);
	myGameOverText.setPosition(sf::Vector2f(-myGameOverText.getLocalBounds().width / 2, -150 - myGameOverText.getLocalBounds().height / 2));

	myRestartButton = Button(sf::Vector2f(0, 0), "RESTART", 60);
	myRestartButton.SetPosition(-myRestartButton.GetText().getLocalBounds().width / 2, 0);

	myShopButton = Button(sf::Vector2f(0, 0), "SHOP", 40);
	myShopButton.SetPosition(myWidth / 2 - myShopButton.GetText().getLocalBounds().width - 10, -myHeight / 2);

	myGameButton = Button(sf::Vector2f(0, 0), "BACK", 40);
	myGameButton.SetPosition(myWidth - myGameButton.GetText().getLocalBounds().width - 20, myHeight - myGameButton.GetText().getLocalBounds().height * 2);

	float tempStartY = -myHeight;
	float tempXPos = -myWidth;
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "NONE", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), ".COM", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "LUL", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "FUN (EPILEPSY WARNING)", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));

	for (int i = 0; i < myTexButtons.size(); i++)
	{
		if (i <11)
			myTexButtons[i].SetPosition(-myWidth, tempStartY + i * 60);
		else
		{
			myTexButtons[i].SetPosition(0, tempStartY + (i- 11) * 60);
		}
	}
}



void Sandbox::OnUpdate()
{
	InputManager::OnUpdate();
	TimeTracker::Update();
	MusicManager::OnUpdate();
	Button::SetScale(sf::Vector2f(myStartWidth / myWidth, myStartHeight / myHeight));
	if (myGameState == Game)
	{
		if (Player::GetDeadFlag())
		{
			if (!myScoreCheckedFlag)
			{
				Window::SetTextField(&myPlayerInput);
				myPlayerText.setString(myPlayerInput);
				myPlayerText.setPosition(sf::Vector2f(-myPlayerText.getLocalBounds().width / 2, 0));
				while (myPlayerInput.length() > 8)
				{
					myPlayerInput.pop_back();
				}

				if (InputManager::GetKeyDown(sf::Keyboard::Enter) && !myPlayerInput.empty())
				{
					CheckScore(Score(myPlayerInput, Player::GetScore()));
					Window::SetTextField(nullptr);
					myScoreCheckedFlag = true;
				}
			}
			else
			{
				myRestartButton.OnUpdate();
				if (myRestartButton.GetClickedFlag())
				{
					Restart();
				}
			}

		}



		EnemyManager::OnUpdate();
		Ball::OnUpdate();
		Player::OnUpdate();
		Healthbar::OnUpdate();



		if ((std::abs(Ball::GetVelocity().x) > 0 || std::abs(Ball::GetVelocity().y > 0)) && !GameStarted)
		{
			GameStarted = true;
			Shake(200);
			sf::Image tempImg = TitleNameTex.copyToImage();
			for (int i = 0; i < myTitleParticleSystem.GetSize(); i++)
			{
				int tempPlace = i * myTitleSplit;
				sf::Color tempCol = tempImg.getPixel(tempPlace % tempImg.getSize().x, myTitleSplit * (tempPlace / tempImg.getSize().x));
				ParticleProps tempProp = ParticleProps();
				if (tempCol == sf::Color::Transparent)
				{
					continue;
				}
				tempProp.ColorBegin = tempCol;
				tempProp.SizeEnd = sf::Vector2f(0, 0);
				tempProp.LifeTime = 3;
				tempProp.Position = TitleText.getPosition() + sf::Vector2f(tempPlace % tempImg.getSize().x * TitleText.getScale().x, (myTitleSplit * tempPlace / tempImg.getSize().x) * TitleText.getScale().x);
				tempProp.PointCount = Random::Int(3, 7);
				tempProp.Velocity = tempProp.Position * 5.f;
				tempProp.VelocityVariation = sf::Vector2f(70, 70);
				tempProp.AngVelVariation = 30;
				myTitleParticleSystem.Emit(tempProp);
			}
		}

		if (!GameStarted)
		{
			myShopButton.OnUpdate();
			if (myShopButton.GetClickedFlag())
			{
				myGameState = Shop;
				myWidth = myStartWidth;
				myHeight = myStartHeight;
			}
		}

		myTitleParticleSystem.OnUpdate();
		if (GameStarted && (myWidth <= myStartWidth || myHeight <= myStartHeight))
		{
			myTempWidth = Math::Lerp(myTempWidth, myStartWidth, 7.f * TimeTracker::GetUnscaledDeltaTime());
			myWidth = (int)myTempWidth;
			if (myWidth > myStartWidth)
				myWidth = myStartWidth;
			myHeight = myStartHeight * myWidth / myStartWidth;
		}
	}
	else if (myGameState == Shop)
	{
		myGameButton.OnUpdate();
		if (myGameButton.GetClickedFlag())
		{
			myGameState = Game;
			Restart();
		}

		for (int i = 0; i < myTexButtons.size(); i++)
		{
			myTexButtons[i].OnUpdate();
		}
	}

	if (myMagnitude > 0)
	{
		myMagnitude -= fmin(myMagnitude * TimeTracker::GetUnscaledDeltaTime() * 10, myMagnitude / 2);
	}
	GetRawWindow()->setView(sf::View(sf::Vector2f(Random::Int(-myMagnitude, myMagnitude + 1), Random::Int(-myMagnitude, myMagnitude + 1)), sf::Vector2f(myWidth, myHeight)));

}
void Sandbox::OnRender(sf::RenderWindow* aWindow)
{
	if (myGameState == Game)
	{
		if (!GameStarted)
			aWindow->draw(TitleText);
		myTitleParticleSystem.OnRender(aWindow);
		EnemyManager::OnRender(aWindow);
		Ball::OnRender(aWindow);
		Player::OnRender(aWindow);
		Healthbar::OnRender(aWindow);

		if (Ball::GetVelocity() == sf::Vector2f(0, 0))
		{
			sf::Vector2f tempStartPos = sf::Vector2f(-Window::CurrentWindow->GetSize().x / 4, -Window::CurrentWindow->GetSize().y / 4);
			sf::Text tempHsText = sf::Text("Highscores:", Player::GetScoreFont(), 20);
			tempHsText.setPosition(tempStartPos);
			aWindow->draw(tempHsText);

			for (short i = 0; i < 10; i++)
			{
				sf::Text tempScoreText = sf::Text(myHighscores[i].Name + ": " + std::to_string(myHighscores[i].Value), Player::GetScoreFont(), 20);
				tempScoreText.setPosition(tempStartPos + sf::Vector2f(0, ((i + 1) * 20) + 20));
				aWindow->draw(tempScoreText);
			}
		}

		if (Player::GetDeadFlag())
		{

			sf::Vector2f tempStartPos = sf::Vector2f(-Window::CurrentWindow->GetSize().x / 2, -Window::CurrentWindow->GetSize().y / 2);
			sf::Text tempHsText = sf::Text("Highscores:", Player::GetScoreFont(), 40);
			tempHsText.setPosition(tempStartPos);
			aWindow->draw(tempHsText);

			for (short i = 0; i < 10; i++)
			{
				sf::Text tempScoreText = sf::Text(myHighscores[i].Name + ": " + std::to_string(myHighscores[i].Value), Player::GetScoreFont(), 40);
				tempScoreText.setPosition(tempStartPos + sf::Vector2f(0, ((i + 1) * 40) + 40));
				aWindow->draw(tempScoreText);
			}


			aWindow->draw(myGameOverText);

			if (!myScoreCheckedFlag)
			{
				aWindow->draw(myPlayerText);
			}
			else
			{
				myRestartButton.OnRender(aWindow);
			}
		}
		if (!GameStarted)
		{
			myShopButton.OnRender(aWindow);
		}
	}
	else if (myGameState == Shop)
	{
		myGameButton.OnRender(aWindow);
		for (int i = 0; i < myTexButtons.size(); i++)
		{
			myTexButtons[i].OnRender(aWindow);
		}
	}

}

void Sandbox::CheckScore(Score aScore)
{
	Score tempScore = aScore;
	Score tempScoreHold;
	bool tempHsFlag = false;
	for (int i = 0; i < 10; i++)
	{
		if (tempScore.Value > myHighscores[i].Value)
		{
			tempHsFlag = true;
			tempScoreHold = myHighscores[i];
			myHighscores[i] = tempScore;
			tempScore = tempScoreHold;
		}
	}
	if (tempHsFlag)
	{
		for (int i = 0; i < 10; i++)
		{
			SaveLoad::Save("HSN" + std::to_string(i), myHighscores[i].Name);
			SaveLoad::Save("HSV" + std::to_string(i), std::to_string(myHighscores[i].Value));
		}
	}
}

void Sandbox::Restart()
{
	EnemyManager::Reset();
	Ball::Reset();
	Player::Reset();
	Healthbar::Reset();
	myTitleParticleSystem = ParticleSystem((TitleNameTex.getSize().x / myTitleSplit) * (TitleNameTex.getSize().y / myTitleSplit));

	Player::SetPosition(sf::Vector2f(0, 65));
	myHeight /= 2;
	myWidth /= 2;
	myTempWidth = myWidth;
	myMagnitude = 0;
	GameStarted = false;
	myScoreCheckedFlag = false;
	TimeTracker::SetTimeScale(1);
}

void Sandbox::Shake(float aMagnitude)
{
	myMagnitude += aMagnitude;
}

Window* BuildWindow()
{
	return new Sandbox("Balls To The Wall", 1240, 720);
}