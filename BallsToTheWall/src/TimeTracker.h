#pragma once
#include <SFML/System/Clock.hpp>
class TimeTracker
{
private:
	static sf::Clock myClock;
	static sf::Time myTime;
	static float myTimeScale;
public:
	static void Update();
	static sf::Time GetTime();
	static float GetDeltaTime();
	static float GetUnscaledDeltaTime();
	static float GetTimeScale();
	static void SetTimeScale(float aValue);
};
