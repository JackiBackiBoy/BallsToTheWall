#pragma once
#include "SFML/Window/Keyboard.hpp"
#include <vector>
#include <SFML\Window\Event.hpp>
class InputManager
{
public:
	static bool GetKey(const sf::Keyboard::Key& aKey);
	static bool GetKeyDown(const sf::Keyboard::Key& aKey);
	static bool GetKeyUp(const sf::Keyboard::Key& aKey);
	static bool GetMouseButton(const sf::Mouse::Button& aButton);
	static bool GetMouseButtonDown(const sf::Mouse::Button& aButton);
	static bool GetMouseButtonUp(const sf::Mouse::Button& aButton);

	static void OnUpdate();
private:
	static std::vector<sf::Keyboard::Key> myPrevKeyBuffer;
	static std::vector<sf::Keyboard::Key> myKeyBuffer;	
	static std::vector<sf::Mouse::Button> myPrevMouseBuffer;
	static std::vector<sf::Mouse::Button> myMouseBuffer;

};

