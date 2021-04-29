#include "HexagonEnemy.h"

HexagonEnemy::HexagonEnemy(const sf::Vector2f& aPosition, const float& aRotation) : Enemy(6, 20, aPosition, aRotation)
{
	myScore = 600;
}

void HexagonEnemy::OnStart()
{
	Enemy::OnStart();
	myAngle = atan2(GetPosition().y, GetPosition().x);
	myLength = Math::Length(GetPosition());
}

void HexagonEnemy::Die() 
{
	if (myTimeSinceHit >= 0.1f)
	{
		sf::Vector2f tempIncidence = Math::Normalized(GetPosition() - Ball::GetPosition());
		tempIncidence.y *= -1;
		float angle = atan2((tempIncidence.y * -1), (tempIncidence.x * -1.f));
		if (angle < 0) angle += Math::Pi * 2;
		angle = ceil(angle / (Math::Pi / 3)) * (Math::Pi / 3) - (Math::Pi / 6);
 		sf::Vector2f tempNormal = sf::Vector2f(cos(angle), sin(angle ));
		sf::Vector2f tempSpecular = Math::Dot(tempNormal, tempIncidence) * 2.f * tempNormal - tempIncidence;
		tempSpecular.x *= -1;
		Ball::SetDirection(tempSpecular);

		myTimeSinceHit = 0;
		myHP--;
		if (myHP <= 0)
		{
			Enemy::Die();
		}
		else 
		{
			sf::Color tempColor = myShape.getFillColor();
			myShape.setFillColor(sf::Color(tempColor.r / 2, tempColor.g / 2, tempColor.b / 2, 255));
		}
	}
}

void HexagonEnemy::OnUpdate()
{
	Enemy::OnUpdate();
	myTimeSinceHit += TimeTracker::GetDeltaTime();
	myAngle += TimeTracker::GetDeltaTime();
	myShape.rotate(Math::ToDegrees(TimeTracker::GetDeltaTime()));
	float tempExtentMod = (sin((myAngle * !myStarting - Math::Pi / (2 * myFrequency)) * myFrequency) * myAmplitude + myAmplitude + 1);
	myShape.setPosition(sf::Vector2f(cos(myAngle), sin(myAngle)) * myLength * tempExtentMod);
	if (sin((myAngle - Math::Pi / (2 * myFrequency)) * myFrequency) < -0.99f)
	{
		myStarting = false;
	}
}

void HexagonEnemy::OnRender(sf::RenderWindow* aWindow)
{
	Enemy::OnRender(aWindow);
}
