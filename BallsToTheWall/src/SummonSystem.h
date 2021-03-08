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
	Triangle = 3,
	Square = 4,
	Hexagon = 6
};
struct SummonProps 
{
	sf::Vector2f Position;
	sf::Color Color;
	float Rotation, AngularVelocity;
	int SizeEnd;
	float CompTime = 5.f;
	EnemyType EnemyType;
};
class SummonSystem
{
public:
	SummonSystem(unsigned int aSummonCount = 10);
	void OnUpdate();
	void OnRender(sf::RenderWindow* aWindow);
	void Summon(const SummonProps& someSummonProps);
private:
	struct SummonData 
	{
		float CompTime = 1.f;
		float Remaining = 0.f;
		std::vector<Enemy> Enemies;
		std::vector<sf::Vector2f> EndPositions;
		sf::Vector2f Position;
		bool Active = false;
		float AngularVelocity;
	};
	std::vector<SummonData> mySummons;
	unsigned int mySummonIndex = 0;
};

