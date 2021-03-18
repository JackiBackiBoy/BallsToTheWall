#pragma once
#include "SFML/Graphics.hpp"
class Button
{
public:
	void OnStart();
	void OnUpdate();
	void OnRender(sf::RenderWindow* aWindow);
	void SetPosition(const int& aX, const int& aY);
	sf::Vector2i GetPosition();
private:
	sf::Rect<int> myRect;

};

