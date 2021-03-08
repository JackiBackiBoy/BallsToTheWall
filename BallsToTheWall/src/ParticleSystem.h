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
	float SizeBegin = 10, SizeEnd = 0, SizeVariation = 3;
	float LifeTime = 1.0f;
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
		float SizeBegin, SizeEnd;
		
		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> myParticles;
	unsigned short myParticleIndex = 999;
};

