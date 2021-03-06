#include "Healthbar.h"
#include "math\Math.h"
#include "core\Window.h"
#include "Player.h"
std::vector<sf::Vector2f> Healthbar::myHealthbar = std::vector<sf::Vector2f>();
float Healthbar::myMaxHealth = 12;
float Healthbar::myHealth = 12;
sf::Vector2f Healthbar::myPosition = sf::Vector2f(30, 50);
bool Healthbar::Resetting = false;
void Healthbar::OnStart()
{
	float scale = 25;
	float tempAngle = Math::Pi * 2 / 10;
	myHealthbar.push_back(sf::Vector2f(myPosition - Window::CurrentWindow->GetRawWindow()->getDefaultView().getSize() / 2.f));
	for (int i = 10; i >= 0; i--) 
	{
		myHealthbar.push_back(sf::Vector2f(cos(tempAngle * i) * scale, sin(tempAngle * i) * scale));
	}
}

void Healthbar::OnUpdate(const float& aDeltaTime)
{
	if (!Resetting) 
	{
		myHealth -= aDeltaTime;
	}
	else
	{
		myHealth += aDeltaTime * 20;
		if (myHealth >= myMaxHealth) 
		{
			myHealth = myMaxHealth;
			Resetting = false;
		}
	}
	if (myHealth <= 0) 
	{
		//dead
		Resetting = true;
	}
}

void Healthbar::OnRender(sf::RenderWindow* aWindow)
{
	float tempHPPercent = myHealth / myMaxHealth;
	int tempVCount = ceil(((myHealthbar.size() - 2) * tempHPPercent)) + 2;

	sf::VertexArray tempVA = sf::VertexArray(sf::PrimitiveType::TriangleFan, tempVCount);
	sf::Color tempHPColor = sf::Color::Color(
		(1 - tempHPPercent) * 255, 
		tempHPPercent * 200, 
		tempHPPercent * 200, 
		100 + 100 * std::max(0.f, std::min(1.f, Math::LengthSqrd((Player::GetPosition() + Window::CurrentWindow->GetRawWindow()->getDefaultView().getSize() / 2.f - myPosition) / 500.f))));

	for (int i = 0; i < tempVCount - 1; i++)
	{
		tempVA[i].position = myHealthbar[i] + tempVA[0].position;
		tempVA[i].color = tempHPColor;
	}
	float tempDiffPercent = (tempHPPercent * 10 - floor(tempHPPercent * 10));
	if (tempHPPercent * 10 == floor(tempHPPercent * 10)) 
	{
		tempDiffPercent = 1;
	}
	tempVA[tempVCount - 1].position = Math::Lerp(myHealthbar[tempVCount - 2], myHealthbar[tempVCount - 1], tempDiffPercent) + tempVA[0].position;
	tempVA[tempVCount - 1].color = tempHPColor;
	aWindow->draw(tempVA);
}

void Healthbar::Reset() 
{
	Resetting = true;
}