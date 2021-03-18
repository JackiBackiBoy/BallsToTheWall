#include "Mouse.h"

sf::Vector2f Mouse::GetPosition()
{
	sf::Vector2i tempPos = sf::Mouse::getPosition(*Window::CurrentWindow->GetRawWindow()) - (sf::Vector2i)Window::CurrentWindow->GetRawWindow()->getDefaultView().getCenter();
	
	return { static_cast<float>(tempPos.x), static_cast<float>(tempPos.y) };
}

