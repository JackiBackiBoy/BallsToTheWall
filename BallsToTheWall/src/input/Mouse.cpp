#include "Mouse.h"

sf::Vector2f Mouse::GetPosition()
{
	sf::Vector2i tempPos = sf::Mouse::getPosition(*Window::CurrentWindow->GetRawWindow()) - (sf::Vector2i)Window::GetCenter();
	float x = Window::CurrentWindow->GetRawWindow()->getView().getSize().x / (float)Window::CurrentWindow->GetRawWindow()->getSize().x;
	float y = Window::CurrentWindow->GetRawWindow()->getView().getSize().y / (float)Window::CurrentWindow->GetRawWindow()->getSize().y;
	return { static_cast<float>(tempPos.x) * x, static_cast<float>(tempPos.y) * y };
}
void Mouse::SetPosition(const sf::Vector2i& aPos)
{
	sf::Mouse::setPosition(aPos + (sf::Vector2i)Window::GetCenter(), *Window::CurrentWindow->GetRawWindow());
}

