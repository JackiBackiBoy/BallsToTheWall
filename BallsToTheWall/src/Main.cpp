#include <iostream>
#include "SFML/Graphics.hpp"
#include "core/Window.h"

extern Window* BuildWindow();

int main()
{
	Window* tempWindow = BuildWindow();
	Window::CurrentWindow = tempWindow;
	Window::CurrentWindow->Run();
	delete tempWindow;
	int Test = 0;
	return 0;
}