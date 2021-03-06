#pragma once
#include "SFML\Graphics.hpp"

class Healthbar
{
public:
	static void OnStart();
	static void OnUpdate();
	static void OnRender(sf::RenderWindow* aWindow);
private:
	static std::vector<sf::Vector2f> myHealthbar;
	static float myMaxHealth;
	static float myHealth;
};

