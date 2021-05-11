#include "Enemy.h"
#include "EnemyManager.h"
#include "Sandbox.h"

Enemy::Enemy(const int& aPointCount, const float& aRadius, const sf::Vector2f& aPosition, const float& aRotation)
{
	float tempRadius = aRadius * Sandbox::GetScaleFactor();
	float tempAngle = Math::Pi * 2 / aPointCount;
	myShape.setPointCount(aPointCount);
	for (int i = 0; i < aPointCount; i++)
	{
		myShape.setPoint(i, sf::Vector2f(cos(tempAngle * i - Math::Pi / (2 * (aPointCount - 2))) * tempRadius, sin(tempAngle * i - Math::Pi / (2 * (aPointCount - 2))) * tempRadius));
	}

	myShape.setFillColor(sf::Color::Color(255, 255, 255, 255));
	if (Sandbox::GetPack() == "Fun")
	{
		myShape.setTexture(nullptr);
	}
	else
	{
		myShape.setTexture(&EnemyManager::GetEnemyTexture());
		myShape.setTextureRect(sf::IntRect(0, 0, EnemyManager::GetEnemyTexture().getSize().x, EnemyManager::GetEnemyTexture().getSize().y));
	}

	myShape.setPosition(aPosition);
	myShape.setRotation(Math::ToDegrees(aRotation + Math::Pi / (2 * (aPointCount - 2))));
}

void Enemy::OnStart()
{

}
void Enemy::Collision()
{
	if (Ball::Intersects(myShape))
	{
		Die();
	}
	if (Intersects(Player::GetShape()))
	{
		Player::Die();
	}
}

void Enemy::OnUpdate()
{
	if (Sandbox::GetPack() == "Fun")
	{
		myShape.setFillColor(Math::ShiftRainbow(myShape.getFillColor(), TimeTracker::GetUnscaledDeltaTime() * 500));
	}
	Collision();
}

void Enemy::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(myShape);
}

void Enemy::Die()
{
	myDeadFlag = true;
}

bool Enemy::IsDead()
{
	return myDeadFlag;
}

void Enemy::SetPosition(const sf::Vector2f& aPosition)
{
	myShape.setPosition(aPosition);
}

void Enemy::SetScale(const sf::Vector2f& aScale)
{
	myShape.setScale(aScale);
}

void Enemy::SetRotation(const float& someDegrees)
{
	myShape.setRotation(someDegrees);
}

void Enemy::Rotate(const float& someDegrees)
{
	myShape.rotate(someDegrees);
}

sf::Vector2f Enemy::GetPosition()
{
	return myShape.getPosition();
}

sf::Vector2f Enemy::GetVelocity()
{
	return myDirection * myVelocity;
}

sf::ConvexShape Enemy::GetShape()
{
	return myShape;
}

int Enemy::GetScore()
{
	return myScore * Player::GetScoreMultiplier();
}

sf::Color Enemy::GetFillColor()
{
	return myShape.getFillColor();
}

void Enemy::SetFillColor(sf::Color aColor)
{
	myShape.setFillColor(aColor);
}

bool Enemy::Intersects(sf::ConvexShape a)
{
	sf::ConvexShape b = myShape;
	// loop over the vertices(-> edges -> axis) of the first polygon
	for (int n = 0; n < 2; n++)
	{
		auto current = a.getPoint(a.getPointCount() - 1);
		current.x *= a.getScale().x;
		current.y *= a.getScale().y;
		current = Math::RotPDeg(current, a.getRotation());
		for (auto i = 0; i < a.getPointCount(); i++)
		{
			// calculate the normal vector of the current edge
			// this is the axis will we check in this loop
			auto next = a.getPoint(i);
			next.x *= a.getScale().x;
			next.y *= a.getScale().y;
			next = Math::RotPDeg(next, a.getRotation());
			auto edge = next - current;

			sf::Vector2f axis = sf::Vector2f(-edge.y, edge.x);

			// loop over all vertices of both polygons and project them
			// onto the axis. We are only interested in max/min projections
			auto aMaxProj = -std::numeric_limits<float>::infinity();
			auto aMinProj = std::numeric_limits<float>::infinity();
			auto bMaxProj = -std::numeric_limits<float>::infinity();
			auto bMinProj = std::numeric_limits<float>::infinity();
			for (int j = 0; j < a.getPointCount(); j++)
			{
				sf::Vector2f tempPoint = a.getPoint(j);
				tempPoint.x *= a.getScale().x;
				tempPoint.y *= a.getScale().y;
				tempPoint = Math::RotPDeg(tempPoint, a.getRotation());
				auto proj = Math::Dot(axis, tempPoint + a.getPosition());
				if (proj < aMinProj) aMinProj = proj;
				if (proj > aMaxProj) aMaxProj = proj;
			}

			for (int j = 0; j < b.getPointCount(); j++)
			{
				sf::Vector2f tempPoint = b.getPoint(j);
				tempPoint.x *= b.getScale().x;
				tempPoint.y *= b.getScale().y;
				tempPoint = Math::RotPDeg(tempPoint, b.getRotation());
				auto proj = Math::Dot(axis, tempPoint + b.getPosition());
				if (proj < bMinProj) bMinProj = proj;
				if (proj > bMaxProj) bMaxProj = proj;
			}

			// now check if the intervals the both polygons projected on the
			// axis overlap. If they don't, we have found an axis of separation and
			// the given polygons cannot overlap
			if ((aMaxProj < bMinProj || aMinProj > bMaxProj))
			{
				return false;
			}
			current = next;
		}
		b = a;
		a = myShape;
	}

	// at this point, we have checked all axis but found no separating axis
	// which means that the polygons must intersect.
	return true;
}