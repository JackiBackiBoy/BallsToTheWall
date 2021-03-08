#include "ParticleSystem.h"
#include "TimeTracker.h"
#include "Random.h"
#include "math\Math.h"

ParticleSystem::ParticleSystem(unsigned int aParticleCount)
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

		p.Shape.move(p.Velocity * TimeTracker::GetDeltaTime());
		p.Shape.rotate(Math::ToDegrees(p.AngularVelocity * TimeTracker::GetDeltaTime()));
	}
}

void ParticleSystem::OnRender(sf::RenderWindow* aWindow)
{
	for (auto& p : myParticles) 
	{
		if (!p.Active) continue;

		float tempLife = p.LifeRemaining / p.LifeTime;

		p.Shape.setFillColor(Math::Lerp(p.ColorEnd, p.ColorBegin, tempLife));
		p.Shape.setScale(Math::Lerp(p.SizeEnd, p.SizeBegin, tempLife));
		aWindow->draw(p.Shape);
	}
}

void ParticleSystem::Emit(const ParticleProps& someParticleProps)
{
	Particle& tempP = myParticles[myParticleIndex];
	tempP.Active = true;

	tempP.Velocity = someParticleProps.Velocity;
	tempP.Velocity.x += someParticleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	tempP.Velocity.y += someParticleProps.VelocityVariation.y * (Random::Float() - 0.5f);
	tempP.AngularVelocity = someParticleProps.AngVel + someParticleProps.AngVelVariation * (Random::Float() - 0.5f);

	tempP.ColorBegin = someParticleProps.ColorBegin;
	tempP.ColorEnd = someParticleProps.ColorEnd;

	tempP.LifeTime = someParticleProps.LifeTime;
	tempP.LifeRemaining = someParticleProps.LifeTime;

	tempP.SizeBegin = someParticleProps.SizeBegin + someParticleProps.SizeVariation * (Random::Float() - 0.5f);
	tempP.SizeEnd = someParticleProps.SizeEnd;

	if (someParticleProps.Shape.getPointCount() == 0) 
	{
		tempP.Shape = sf::ConvexShape(someParticleProps.PointCount);
		float tempAngleInc = Math::Pi * 2.f / tempP.Shape.getPointCount();
		for (int i = 0; i < tempP.Shape.getPointCount(); i++)
		{
			tempP.Shape.setPoint(i, sf::Vector2f(cos(tempAngleInc * i), sin(tempAngleInc * i)));
		}
	}
	else tempP.Shape = someParticleProps.Shape;
	tempP.Shape.setPosition(someParticleProps.Position);
	tempP.Shape.setRotation(Math::ToDegrees(someParticleProps.Rotation + someParticleProps.RotationVariation * (Random::Float() - 0.5f)));

	if (--myParticleIndex < 0) myParticleIndex = myParticles.size() - 1;
}


