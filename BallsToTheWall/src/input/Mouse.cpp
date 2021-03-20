#include "Mouse.h"

sf::Vector2f Mouse::GetPosition()
{
	sf::Vector2i tempPos = sf::Mouse::getPosition(*Window::CurrentWindow->GetRawWindow()) - (sf::Vector2i)Window::GetCenter();
	
	return { static_cast<float>(tempPos.x), static_cast<float>(tempPos.y) };
}
void Mouse::SetPosition(const sf::Vector2i& aPos)
{
	sf::Mouse::setPosition(aPos + (sf::Vector2i)Window::GetCenter(), *Window::CurrentWindow->GetRawWindow());
}

