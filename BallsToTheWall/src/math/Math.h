#ifndef MATH_HEADER
#define MATH_HEADER

#include "SFML/System.hpp"

class Math
{
public:
	~Math() {};

	inline static float ToDegrees(const float& someRadians) { return (180 / Pi) * someRadians; }
	inline static float ToRadians(const float& someDegrees) { return (Pi / 180) * someDegrees; }
	inline static sf::Vector2f Normalized(sf::Vector2f aVector)
	{
		float tempMag = std::sqrt(aVector.x * aVector.x - aVector.y * aVector.y);
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
		sf::Vector2f tempDiff = aVector0 - aVector1;
		tempDiff = sf::Vector2f(std::abs(tempDiff.x), std::abs(tempDiff.y));
		return std::sqrt(tempDiff.x * tempDiff.x + tempDiff.y * tempDiff.y);
	}
	static constexpr double Pi = 3.14159265358979323846;

private:
	Math() {};
};
#endif