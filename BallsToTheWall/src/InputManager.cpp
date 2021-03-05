#include "InputManager.h"
#include "core/Window.h"

std::vector < sf::Keyboard::Key> InputManager::myPrevKeyBuffer = std::vector<sf::Keyboard::Key>();
std::vector < sf::Keyboard::Key> InputManager::myKeyBuffer = std::vector<sf::Keyboard::Key>();

bool InputManager::GetKey(sf::Keyboard::Key aKey)
{
	if (!Window::CurrentWindow->GetRawWindow()->hasFocus())
	{
		return false;
	}
	return sf::Keyboard::isKeyPressed(aKey);
}

bool InputManager::GetKeyDown(sf::Keyboard::Key aKey)
{

	//if key is down
	if (GetKey(aKey))
	{
		//if key doesn't exists in buffer add it
		if (std::find(myKeyBuffer.begin(), myKeyBuffer.end(), aKey) == myKeyBuffer.end())
		{
			myKeyBuffer.push_back(aKey);
		}
		//if Key isnt contained in PreviousKeyBuffer
		if (std::find(myPrevKeyBuffer.begin(), myPrevKeyBuffer.end(), aKey) == myPrevKeyBuffer.end())
		{
			return true;
		}
	}
	return false;
}

bool InputManager::GetKeyUp(sf::Keyboard::Key aKey)
{
	//if key isn't down
	if (!GetKey(aKey))
	{
		//if Key is contained in PreviousKeyBuffer
		if (std::find(myPrevKeyBuffer.begin(), myPrevKeyBuffer.end(), aKey) != myPrevKeyBuffer.end())
		{
			return true;
		}
	}
	//if key is down
	else
	{
		//if key doesn't exists in buffer add it
		if (std::find(myKeyBuffer.begin(), myKeyBuffer.end(), aKey) == myKeyBuffer.end())
		{
			myKeyBuffer.push_back(aKey);
		}
	}
	return false;
}
void InputManager::OnUpdate()
{
	myPrevKeyBuffer = myKeyBuffer;
	myKeyBuffer.clear();
}
