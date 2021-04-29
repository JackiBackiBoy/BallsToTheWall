#pragma once
#include "SFML/Graphics.hpp"
class Button
{
public:
	Button();
	Button(sf::Vector2f aPos, std::string aString, int aSize);
	void OnStart();
	void OnUpdate(float xScale, float yScale);
	void OnRender(sf::RenderWindow* aWindow);
	void SetPosition(const int& aX, const int& aY);
	sf::Text GetText();
	sf::Vector2i GetPosition();
	bool GetClickedFlag();
private:
	sf::Rect<int> myRect;
	sf::Text myText;
	bool myClickedFlag;

};

