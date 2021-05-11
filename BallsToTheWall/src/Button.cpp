#include "Button.h"
#include "input/Mouse.h"
#include "Player.h"
#include "core/Window.h"
#include <iostream>
#include "InputManager.h"
#include "Sandbox.h"

bool Button::myButtonHovered = false;

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
	sf::Vector2f tempPos = Mouse::GetPosition(false);
	sf::FloatRect tempRect = myText.getLocalBounds();
	tempRect.left += myText.getPosition().x;
	tempRect.top += myText.getPosition().y;
	tempRect.width = tempRect.width;
	tempRect.height = tempRect.height;

	if (tempRect.contains(tempPos))
	{
		myButtonHovered = true;
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

void Button::UpdateHover()
{
	myButtonHovered = false;
}

bool Button::GetHoverFlag()
{
	return myButtonHovered;
}
