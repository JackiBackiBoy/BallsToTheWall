#ifndef KEYBOARD_HEADER
#define KEYBOARD_HEADER

#include "SFML/Window.hpp"
#include <unordered_map>

class Keyboard
{
public:
	~Keyboard() {};

	static bool IsKeyDown(const sf::Keyboard::Key& aKey);
	static bool IsKeyDownOnce(const sf::Keyboard::Key& aKey);

	static void UpdateKeyStates();

private:
	Keyboard();

	static std::unordered_map<sf::Keyboard::Key, bool> myKeyStates;
};
#endif