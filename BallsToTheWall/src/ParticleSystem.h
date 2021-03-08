#pragma once
#include <iostream>
#include <vector>
#include "SFML\Graphics.hpp"
#include "math\Math.h"
struct ParticleProps 
{
	sf::Vector2f Position;
	sf::Vector2f Velocity, VelocityVariation;
	sf::Color ColorBegin, ColorEnd;
	float Rotation = 0, RotationVariation = Math::Pi * 2.f, AngularVelocity = 0.1f;
	sf::Vector2f SizeBegin = { 10, 10 }, SizeEnd = { 0, 0 }, SizeVariation = { 3, 3 };
	float LifeTime = 1.0f;
	int PointCount = 4;
};
class ParticleSystem
{
public:
	ParticleSystem(unsigned short aParticleCount = 1000);
	void OnUpdate();
	void OnRender(sf::RenderWindow* aWindow);
	void Emit(const ParticleProps& someParticleProps);
private:
	struct Particle 
	{
		sf::Vector2f Position;
		sf::Vector2f Velocity, VelocityVariation;
		sf::Color ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float AngularVelocity;
		sf::Vector2f SizeBegin, SizeEnd;
		
		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		int PointCount;
		bool Active = false;
	};
	std::vector<Particle> myParticles;
	unsigned short myParticleIndex = 999;
};

