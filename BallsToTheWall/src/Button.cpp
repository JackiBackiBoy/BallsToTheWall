#include "Button.h"
#include "input/Mouse.h"
#include "Player.h"
#include "core/Window.h"
#include <iostream>
#include "InputManager.h"

sf::Vector2f Button::myScale = sf::Vector2f(1, 1);

Button::Button()
{
}

Button::Button(sf::Vector2f aPos, std::string aString, int aSize)
{
	myClickedFlag = false;
	myText = sf::Text(aString, Player::GetScoreFont(), aSize);
	myText.setPosition(aPos);
	myText.setFillColor(sf::Color::White);
}

void Button::OnStart()
{
}

void Button::OnUpdate()
{
	sf::Vector2f tempPos = Mouse::GetPosition();
	sf::FloatRect tempRect = myText.getGlobalBounds();
	tempRect.width = tempRect.width * myScale.x;
	tempRect.height = tempRect.height * myScale.y;
	
	if (myScale.x == 2)//Hemskt
	{
		tempRect.left += myText.getPosition().x;
		tempRect.top += myText.getPosition().y +10;
	}

	if (tempRect.contains(tempPos))
	{
		myText.setFillColor(sf::Color::Magenta);
		if (InputManager::GetMouseButtonDown(sf::Mouse::Left))
		{
			myClickedFlag = true;
		}
	}
	else
	{
		myText.setFillColor(sf::Color::White);
	}
}

void Button::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(myText);
}

void Button::SetPosition(const int& aX, const int& aY)
{
	myText.setPosition(aX, aY);
}

sf::Text Button::GetText()
{
	return myText;
}

sf::Vector2i Button::GetPosition()
{
	return sf::Vector2i();
}

bool Button::GetClickedFlag()
{
	if (myClickedFlag)
	{
		myClickedFlag = false;
		return true;
	}
	return false;
}

void Button::SetScale(sf::Vector2f aScale)
{
	myScale = aScale;
}
