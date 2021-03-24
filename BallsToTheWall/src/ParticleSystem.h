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
	float Rotation = 0, RotationVariation = Math::Pi * 2.f, AngVel = 1.f, AngVelVariation = 0.1f;
	sf::Vector2f SizeBegin = { 10, 10 }, SizeEnd = { 0, 0 }, SizeVariation = { 3, 3 };
	float LifeTime = 1.0f;
	sf::ConvexShape Shape;
	int PointCount = 4;
};
class ParticleSystem
{
public:
	ParticleSystem(const unsigned int& aParticleCount = 1000);
	void OnUpdate();
	void OnRender(sf::RenderWindow* aWindow);
	void Emit(const ParticleProps& someParticleProps);
	int GetSize();
private:
	struct Particle 
	{
		sf::Vector2f Velocity;
		sf::Color ColorBegin, ColorEnd;
		float AngularVelocity;
		sf::Vector2f SizeBegin, SizeEnd;
		
		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		sf::ConvexShape Shape;
		bool Active = false;
	};
	std::vector<sf::Vertex> GetVerts(Particle aParticle);
	std::vector<Particle> myParticles;
	unsigned int myParticleIndex = 0;
};

