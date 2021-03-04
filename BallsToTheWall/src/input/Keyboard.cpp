#include "Keyboard.h"
#include "core/Window.h"

bool Keyboard::IsKeyDown(const sf::Keyboard::Key& aKey)
{
	// Check if the window is in focus, if not return false
	if (!Window::CurrentWindow->GetRawWindow()->hasFocus())
	{
		return false;
	}

	return sf::Keyboard::isKeyPressed(aKey);
}

bool Keyboard::IsKeyDownOnce(const sf::Keyboard::Key& aKey)
{
	if (!IsKeyDown(aKey) && myKeyStates[aKey])
	{
		return true;
	}

	return false;
}

void Keyboard::UpdateKeyStates()
{
	for (int i = sf::Keyboard::Key::Unknown; i != sf::Keyboard::Key::KeyCount; i++)
	{
		myKeyStates[static_cast<sf::Keyboard::Key>(i)] = IsKeyDown(static_cast<sf::Keyboard::Key>(i));
	}
}

Keyboard::Keyboard()
{
	// Add all keys to the key states list
	for (int i = sf::Keyboard::Key::Unknown; i != sf::Keyboard::Key::KeyCount; i++)
	{
		myKeyStates.insert({ static_cast<sf::Keyboard::Key>(i), false });
	}
}

std::unordered_map<sf::Keyboard::Key, bool> Keyboard::myKeyStates;