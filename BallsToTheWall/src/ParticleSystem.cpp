#include "ParticleSystem.h"
#include "TimeTracker.h"
#include "Random.h"
#include "math\Math.h"

ParticleSystem::ParticleSystem(unsigned short aParticleCount)
{
	myParticles.resize(aParticleCount);
}

void ParticleSystem::OnUpdate()
{
	for (auto& p : myParticles) 
	{
		if (!p.Active) continue;
		
		p.LifeRemaining -= TimeTracker::GetDeltaTime();
		if (p.LifeRemaining <= 0.0f)
		{
			p.Active = false;
			continue;
		}

		p.Position += p.Velocity * TimeTracker::GetDeltaTime();
		p.Rotation += p.AngularVelocity * TimeTracker::GetDeltaTime();
	}
}

void ParticleSystem::OnRender(sf::RenderWindow* aWindow)
{
	for (auto& p : myParticles) 
	{
		if (!p.Active) continue;

		float tempLife = p.LifeRemaining / p.LifeTime;

		sf::Color tempC = Math::Lerp(p.ColorEnd, p.ColorBegin, tempLife);

		sf::Vector2f tempSize = Math::Lerp(p.SizeEnd, p.SizeBegin, tempLife);

		sf::VertexArray tempVA = sf::VertexArray(sf::PrimitiveType::TriangleFan, p.PointCount);
		float tempAngleInc = Math::Pi * 2.f / p.PointCount;
		for (int i = 0; i < p.PointCount; i++) 
		{
			tempVA[i].position = sf::Vector2f(cos(p.Rotation + tempAngleInc * i) * tempSize.x, sin(p.Rotation + tempAngleInc * i) * tempSize.y) + p.Position;
			tempVA[i].color = tempC;
		}
		aWindow->draw(tempVA);
	}
}

void ParticleSystem::Emit(const ParticleProps& someParticleProps)
{
	Particle& tempP = myParticles[myParticleIndex];
	tempP.Active = true;
	tempP.Position = someParticleProps.Position;
	tempP.Rotation = someParticleProps.Rotation;
	tempP.Rotation += someParticleProps.RotationVariation * (Random::Float() - 0.5f);

	tempP.Velocity = someParticleProps.Velocity;
	tempP.Velocity.x += someParticleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	tempP.Velocity.y += someParticleProps.VelocityVariation.y * (Random::Float() - 0.5f);

	tempP.ColorBegin = someParticleProps.ColorBegin;
	tempP.ColorEnd = someParticleProps.ColorEnd;

	tempP.LifeTime = someParticleProps.LifeTime;
	tempP.LifeRemaining = someParticleProps.LifeTime;
	tempP.SizeBegin = someParticleProps.SizeBegin + someParticleProps.SizeVariation * (Random::Float() - 0.5f);
	tempP.SizeEnd = someParticleProps.SizeEnd;

	tempP.PointCount = someParticleProps.PointCount;

	if (--myParticleIndex < 0) myParticleIndex = myParticles.size() - 1;
}


