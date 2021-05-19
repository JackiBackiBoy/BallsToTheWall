#include "Sandbox.h"
#include"InputManager.h"
#include "Button.h"

int myGoldenOctagons = 0;

float Sandbox::myMagnitude = 0;
std::string Sandbox::myPack = "Default";
float Sandbox::myScaleFactor = 0;
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

sf::Color myHighscoreTextFun = sf::Color::White;


Button myGameButton;
std::vector<Button> myTexButtons;
enum TexturePack
{
	Default,
	DotCom,
	Lul,
	Fun,
	Inception,
	SpreadIt
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

	myGoldenOctagons = std::stoi(SaveLoad::Load("GOcts"));

	float tempRatio = myWidth / (float)myHeight;
	float tempDefaultRatio = 1240.f / 720.f;

	myScaleFactor = (myWidth / 1240.f) * (tempDefaultRatio / tempRatio);

	myStartWidth = myWidth;
	myStartHeight = myHeight;

	TitleNameTex.loadFromFile("Assets/GameName.png");
	TitleText = sf::Sprite(TitleNameTex);
	TitleText.setScale(sf::Vector2f(0.5f, 0.5f) * myScaleFactor);
	TitleText.setPosition(sf::Vector2f(-(int)TitleNameTex.getSize().x * TitleText.getScale().x / 2, -(int)TitleNameTex.getSize().y * TitleText.getScale().y / 2));
	myTitleParticleSystem = ParticleSystem((TitleNameTex.getSize().x / myTitleSplit) * (TitleNameTex.getSize().y / myTitleSplit));

	Options::Load();

	Random::RSeed();
	EnemyManager::OnStart();
	Ball::OnStart();
	Player::OnStart();
	Healthbar::OnStart();
	MusicManager::Start("EDM 2");

	Player::SetPosition(sf::Vector2f(0, 65) * myScaleFactor);
	Mouse::SetPosition(sf::Vector2i(0, 20));
	myHeight /= 2;
	myWidth /= 2;
	myTempWidth = myWidth;

	myPlayerText = sf::Text("", Player::GetScoreFont(), 50);
	myGameOverText = sf::Text("GAME OVER", Player::GetScoreFont(), 100);
	myGameOverText.setPosition(sf::Vector2f(-myGameOverText.getLocalBounds().width / 2, -150 - myGameOverText.getLocalBounds().height / 2));

	myRestartButton = Button(sf::Vector2f(0, 0), "RESTART", 60);
	myRestartButton.SetPosition(-myRestartButton.GetText().getLocalBounds().width / 2, 0);

	myShopButton = Button(sf::Vector2f(0, 0), "SHOP", 60);
	myShopButton.SetPosition((myStartWidth / 2) - myShopButton.GetText().getLocalBounds().width - 20, -myStartHeight / 2);

	myGameButton = Button(sf::Vector2f(0, 0), "BACK", 40);
	myGameButton.SetPosition(myWidth - myGameButton.GetText().getLocalBounds().width - 20, myHeight - myGameButton.GetText().getLocalBounds().height * 2);

	float tempStartY = -myHeight;
	float tempXPos = -myWidth;
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "DEFAULT", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), ".COM", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "LUL", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "FUN (EPILEPSY WARNING)", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "INCEPTION", 60));
	myTexButtons.push_back(Button(sf::Vector2f(0, 0), "SPREAD IT", 60));

	for (int i = 0; i < myTexButtons.size(); i++)
	{
		if (i < 11)
			myTexButtons[i].SetPosition(-myWidth, tempStartY + i * 60);
		else
		{
			myTexButtons[i].SetPosition(0, tempStartY + (i - 11) * 60);
		}
	}

	Restart();
}



void Sandbox::OnUpdate()
{
	InputManager::OnUpdate();
	TimeTracker::Update();
	MusicManager::OnUpdate();
	Button::UpdateHover();
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
			if (myTexButtons[i].GetClickedFlag())
			{
				TitleText.setColor(sf::Color::White);

				switch ((TexturePack)i)
				{
				case TexturePack::Default:
					myPack = "Default";
					break;
				case TexturePack::DotCom:
					myPack = "Com";
					if (MusicManager::GetCurrent() != "Soviet Techno")
					{
						MusicManager::Start("Soviet Techno");
					}
					break;
				case TexturePack::Lul:
					myPack = "Emoji";
					break;
				case TexturePack::Fun:
					myPack = "Fun";
					break;
				case TexturePack::Inception:
					myPack = "Inception";
					break;
				case TexturePack::SpreadIt:
					myPack = "SpreadIt";
					break;
				}
				if (myPack != "Com" && MusicManager::GetCurrent() != "EDM 2")
				{
					MusicManager::Start("EDM 2");
				}
			}
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
	OnRenderGame(aWindow);
	sf::View tempView = Window::CurrentWindow->GetRawWindow()->getView();
	Window::CurrentWindow->GetRawWindow()->setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(myStartWidth, myStartHeight)));
	OnRenderUi(aWindow);
	Window::CurrentWindow->GetRawWindow()->setView(tempView);

}
void DecreaseGold(int someAmount)
{
	myGoldenOctagons -= someAmount;
	SaveLoad::Save("GOcts", std::to_string(myGoldenOctagons));
}
void IncreaseGold(int someAmount)
{
	myGoldenOctagons += someAmount;
	SaveLoad::Save("GOcts", std::to_string(myGoldenOctagons));
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

	Player::SetPosition(sf::Vector2f(0, 65) * myScaleFactor);
	myHeight = myStartHeight / 2;
	myWidth = myStartWidth / 2;
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

std::string Sandbox::GetPack()
{
	return myPack;
}
float Sandbox::GetScaleFactor()
{
	return myScaleFactor;
}

void Sandbox::OnRenderUi(sf::RenderWindow* aWindow)
{
	if (myGameState == Game)
	{
		if (GameStarted)
			Healthbar::OnRender(aWindow);

		if (!GameStarted || Player::GetDeadFlag())
		{
			sf::Vector2f tempStartPos = sf::Vector2f(-Window::CurrentWindow->GetSize().x / 2, -Window::CurrentWindow->GetSize().y / 2);
			sf::Text tempHsText = sf::Text("Highscores:", Player::GetScoreFont(), 40);
			tempHsText.setPosition(tempStartPos);
			if (myPack == "Fun")
			{
				myHighscoreTextFun = Math::ShiftRainbow(myHighscoreTextFun, TimeTracker::GetUnscaledDeltaTime() * 400);
				tempHsText.setFillColor(myHighscoreTextFun);
			}
			aWindow->draw(tempHsText);

			sf::Color tempFun = myHighscoreTextFun;
			for (short i = 0; i < 10; i++)
			{
				sf::Text tempScoreText = sf::Text(myHighscores[i].Name + ": " + std::to_string(myHighscores[i].Value), Player::GetScoreFont(), 40);
				tempScoreText.setPosition(tempStartPos + sf::Vector2f(0, ((i + 1) * 40) + 40));
				if (myPack == "Fun")
				{
					tempFun = Math::ShiftRainbow(tempFun, (10 - i) * 3);
					tempScoreText.setFillColor(tempFun);
				}
				aWindow->draw(tempScoreText);
			}
		}

		if (Player::GetDeadFlag())
		{
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

void Sandbox::OnRenderGame(sf::RenderWindow* aWindow)
{
	if (myGameState == Game)
	{
		if (!GameStarted)
		{
			if (myPack == "Fun")
			{
				TitleText.setColor(Math::ShiftRainbow(TitleText.getColor(), TimeTracker::GetUnscaledDeltaTime() * 700.f));
			}
			aWindow->draw(TitleText);
		}
		myTitleParticleSystem.OnRender(aWindow);
		EnemyManager::OnRender(aWindow);
		Ball::OnRender(aWindow);
		Player::OnRender(aWindow);
	}

}

Window* BuildWindow()
{
	return new Sandbox("Balls To The Wall", sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
}