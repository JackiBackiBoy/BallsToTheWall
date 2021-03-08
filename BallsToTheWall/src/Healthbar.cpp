#include "Healthbar.h"
#include "math\Math.h"
#include "core\Window.h"
#include "TimeTracker.h"
#include "Player.h"
#include "Ball.h"

std::vector<sf::Vector2f> Healthbar::myHealthbar = std::vector<sf::Vector2f>();
sf::Vector2f Healthbar::myPosition = sf::Vector2f(30, 30);
float Healthbar::myMaxHealth = 12;
float Healthbar::myHealth;
bool Healthbar::Resetting = false;

void Healthbar::OnStart()
{
	myHealth = myMaxHealth;
	float scale = 25;
	float tempAngle = Math::Pi * 2 / 10;
	myHealthbar.push_back(sf::Vector2f(myPosition - Window::CurrentWindow->GetRawWindow()->getDefaultView().getSize() / 2.f));
	for (int i = 10; i >= 0; i--) 
	{
		myHealthbar.push_back(sf::Vector2f(cos(tempAngle * i) * scale, sin(tempAngle * i) * scale));
	}
}

void Healthbar::OnUpdate()
{
	if (!Resetting && Math::LengthSqrd(Ball::GetVelocity()) != 0)
	{
		float tempHPScale = 2.2f - ( std::min(Math::LengthSqrd(Ball::GetVelocity()), 999999.f) / 1000000);
		myHealth -= TimeTracker::GetDeltaTime() * tempHPScale;
	}
	else
	{
		myHealth += TimeTracker::GetDeltaTime() * 20;
		if (myHealth >= myMaxHealth) 
		{
			myHealth = myMaxHealth;
			Resetting = false;
		}
	}
	if (myHealth <= 0) 
	{
		Player::Die();

	}
}

void Healthbar::OnRender(sf::RenderWindow* aWindow)
{
	if (Player::GetDeadFlag())
		return;

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