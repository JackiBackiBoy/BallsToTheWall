#pragma once
#include <iostream>
#include <vector>
#include "SFML\Graphics.hpp"
#include "math\Math.h"
#include "TriangleEnemy.h"
#include "SquareEnemy.h"
#include "HexagonEnemy.h"
enum EnemyType
{
	Triangle = 0,
	Square = 1,
	Hexagon = 2
};
struct SummonProps 
{
	sf::Vector2f Position;
	sf::Color Color = sf::Color(200, 0, 0, 255);
	float Rotation = 0, AngularVelocity = Math::Pi / 2.5f;
	float CompTime = 5.f;
	EnemyType EnemyType;
	bool* Sector;
};
class SummonSystem
{
public:
	SummonSystem(const unsigned int& aSummonCount = 10);
	void OnUpdate();
	void OnRender(sf::RenderWindow* aWindow);
	void Summon(const SummonProps& someSummonProps);
private:
	struct SummonData 
	{
		float CompTime = 1.f;
		float Remaining = 0.f;
		std::vector<Enemy*> Enemies;
		std::vector<sf::Vector2f> EndPositions;
		sf::Vector2f Position;
		bool Active = false;
		float AngularVelocity;
		float Rotation;
		bool* Sector;
	};
	std::vector<SummonData> mySummons;
	unsigned int mySummonIndex = 0;
};

