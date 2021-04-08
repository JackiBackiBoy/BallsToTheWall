#ifndef MATH_HEADER
#define MATH_HEADER

#include "SFML/System.hpp"

class Math
{
public:
	~Math() {};


	inline static float Lerp(const float& aStartValue, const float& anEndValue, const float& aPercentage)
	{
		return ((1.0f - aPercentage) * aStartValue) + (aPercentage * anEndValue);
	}

	inline static sf::Vector2f Lerp(const sf::Vector2f& aStartValue, const sf::Vector2f& anEndValue, const float& aPercentage)
	{
		return ((1.0f - aPercentage) * aStartValue) + (aPercentage * anEndValue);
	}

	inline static sf::Color Lerp(const sf::Color& aStartValue, const sf::Color& anEndValue, const float& aPercentage)
	{
		return sf::Color(
			(1.0f - aPercentage) * aStartValue.r + aPercentage * anEndValue.r,
			(1.0f - aPercentage) * aStartValue.g + aPercentage * anEndValue.g,
			(1.0f - aPercentage) * aStartValue.b + aPercentage * anEndValue.b,
			(1.0f - aPercentage) * aStartValue.a + aPercentage * anEndValue.a);
	}

	inline static sf::Vector2f RotPDeg(const sf::Vector2f& aPoint, const float& anAngle)
	{
		return RotPRad(aPoint, ToRadians(anAngle));
	}

	inline static sf::Vector2f RotPRad(const sf::Vector2f& aPoint, const float& anAngle)
	{
		return sf::Vector2f(aPoint.x * cos(anAngle) - aPoint.y * sin(anAngle), aPoint.x * sin(anAngle) + aPoint.y * cos(anAngle));
	}

	inline static float ToDegrees(const float& someRadians) { return (180 / Pi) * someRadians; }
	inline static float ToRadians(const float& someDegrees) { return (Pi / 180) * someDegrees; }
	inline static float LengthSqrd(const sf::Vector2f& aVector)
	{
		return aVector.x * aVector.x + aVector.y * aVector.y;
	}
	inline static float Length(const sf::Vector2f& aVector)
	{
		return std::sqrt(LengthSqrd(aVector));
	}
	inline static sf::Vector2f Normalized(const sf::Vector2f& aVector)
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
	inline static float Distance(const sf::Vector2f& aVector0, const sf::Vector2f& aVector1)
	{
		return(Length(aVector0 - aVector1));
	}
	inline static float Dot(const sf::Vector2f& aVector0, const sf::Vector2f& aVector1)
	{
		return aVector0.x * aVector1.x + aVector0.y * aVector1.y;
	}
	inline static float NDot(const sf::Vector2f& aVector0, const sf::Vector2f& aVector1)
	{
		return Dot(Normalized(aVector0), Normalized(aVector1));
	}
	static constexpr double Pi = 3.14159265358979323846;

	inline static sf::Vector3f ColorToHsv(sf::Color aColor)
	{
		sf::Vector3f tempHsv = sf::Vector3f(0, 0, 0);
		float r = aColor.r / 255.f;
		float g = aColor.g / 255.f;
		float b = aColor.b / 255.f;
		float cMax = std::max(std::max(r, g), b);
		float cMin = std::min(std::min(r, g), b);
		float delta = cMax - cMin;

		if (delta == 0)tempHsv.x = 0;
		else if (cMax == r)tempHsv.x = 60 * fmod((g - b) / delta, 6.f);
		else if (cMax == g)tempHsv.x = 60 * ((b - r) / delta + 2);
		else if (cMax == b)tempHsv.x = 60 * ((r - g) / delta + 4);

		if (cMax == 0)tempHsv.y = 0;
		else tempHsv.y = delta / cMax;

		tempHsv.z = cMax;

		return tempHsv;
	}

	inline static sf::Color HsvToColor(sf::Vector3f aHsv)
	{
		float c = aHsv.z * aHsv.y;
		float x = c * (1 - std::abs(fmod(aHsv.x / 60, 2) - 1));
		float m = aHsv.z - c;
		float r, g, b = 0;
		if (aHsv.x >= 300)
		{
			r = c;
			g = 0;
			b = x;
		}
		else if (aHsv.x >= 240)
		{
			r = x;
			g = 0;
			b = c;
		}
		else if (aHsv.x >= 180)
		{
			r = 0;
			g = x;
			b = c;
		}
		else if (aHsv.x >= 120)
		{
			r = 0;
			g = c;
			b = x;
		}
		else if (aHsv.x >= 60)
		{
			r = x;
			g = c;
			b = 0;
		}
		else
		{
			r = c;
			g = x;
			b = 0;
		}

		return sf::Color((r + m) * 255, (g + m) * 255, (b + m) * 255);


	}

	inline static sf::Color ShiftRainbow(sf::Color aColor, float aValue)
	{
		sf::Vector3f tempHsv = ColorToHsv(aColor);
		tempHsv.x += aValue;
		tempHsv.y = 1;
		tempHsv.z = 1;

		sf::Color tempCol = HsvToColor(tempHsv);
		return sf::Color(tempCol.r, tempCol.g, tempCol.b, aColor.a);
	}

private:
	Math() {};
};
#endif