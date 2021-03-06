#pragma once
#include "SFML\Graphics.hpp"

class Healthbar
{
public:
	static void OnStart();
	static void OnUpdate();
	static void OnRender(sf::RenderWindow* aWindow);
	static void Reset();
private:
	static std::vector<sf::Vector2f> myHealthbar;
	static sf::Vector2f myPosition;
	static float myMaxHealth;
	static float myHealth;
	static bool Resetting;
	static sf::Color myFun;
};

