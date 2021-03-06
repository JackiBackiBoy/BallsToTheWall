#pragma once
#include "SFML/Window/Keyboard.hpp"
#include <vector>
#include <SFML\Window\Event.hpp>
class InputManager
{
public:
	static bool GetKey(sf::Keyboard::Key aKey);
	static bool GetKeyDown(sf::Keyboard::Key aKey);
	static bool GetKeyUp(sf::Keyboard::Key aKey);
	static bool GetMouseButton(sf::Mouse::Button aButton);
	static bool GetMouseButtonDown(sf::Mouse::Button aButton);
	static bool GetMouseButtonUp(sf::Mouse::Button aButton);

	static void OnUpdate();
private:
	static std::vector < sf::Keyboard::Key> myPrevKeyBuffer;
	static std::vector < sf::Keyboard::Key> myKeyBuffer;	
	static std::vector < sf::Mouse::Button> myPrevMouseBuffer;
	static std::vector < sf::Mouse::Button> myMouseBuffer;

};

