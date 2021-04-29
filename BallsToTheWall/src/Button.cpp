#include "Button.h"
#include "input/Mouse.h"
#include "Player.h"
#include "core/Window.h"
#include <iostream>
#include "InputManager.h"

Button::Button()
{
}

Button::Button(sf::Vector2f aPos,std::string aString, int aSize)
{
    myClickedFlag = false;
    myText = sf::Text(aString, Player::GetScoreFont(), aSize);
    myText.setPosition(aPos);
    myText.setFillColor(sf::Color::White);
    //myRect = sf::Rect<int>(myText.getPosition(), myText.getLocalBounds().);
}

void Button::OnStart()
{
}

void Button::OnUpdate(float xScale, float yScale)
{
    sf::Vector2f tempPos = Mouse::GetPosition();
    sf::FloatRect tempRect = myText.getGlobalBounds();
    tempRect.width = tempRect.width * xScale;
    tempRect.height = tempRect.height * yScale;
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
