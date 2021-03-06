#ifndef MATH_HEADER
#define MATH_HEADER

#include "SFML/System.hpp"

class Math
{
public:
	~Math() {};

	inline static float ToDegrees(const float& someRadians) { return (180 / Pi) * someRadians; }
	inline static float ToRadians(const float& someDegrees) { return (Pi / 180) * someDegrees; }
	inline static float LengthSqrd(sf::Vector2f aVector)
	{
		return aVector.x * aVector.x + aVector.y * aVector.y;
	}
	inline static float Length(sf::Vector2f aVector)
	{
		return std::sqrt(LengthSqrd(aVector));
	}
	inline static sf::Vector2f Normalized(sf::Vector2f aVector)
	{
		float tempMag = Length(aVector);
		if (tempMag > 0)
		{
			return sf::Vector2f(aVector.x / tempMag, aVector.y / tempMag);
		}
		else
		{
			return aVector;
		}
	}
	inline static float Distance(sf::Vector2f aVector0, sf::Vector2f aVector1)
	{
		return(Length(aVector0 - aVector1));
	}
	inline static float Dot(sf::Vector2f aVector0, sf::Vector2f aVector1) 
	{
		return aVector0.x * aVector1.x + aVector0.y * aVector1.y;
	}
	inline static float NDot(sf::Vector2f aVector0, sf::Vector2f aVector1)
	{
		return Dot(Normalized(aVector0), Normalized(aVector1));
	}
	static constexpr double Pi = 3.14159265358979323846;

private:
	Math() {};
};
#endif