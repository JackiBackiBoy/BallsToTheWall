#include "Window.h"
#include "math/Math.h"
#include "input/Keyboard.h"

void Window::Run()
{
	myPixel = sf::RectangleShape({ 1, 1 });
	myRawWindow = new sf::RenderWindow(sf::VideoMode(myWidth, myHeight), myTitle);

	// OnStart
	Window::OnStart();
	OnStart();

	while (myRawWindow->isOpen())
	{
		// OnUpdate
		OnUpdate();
		Window::OnUpdate();

		sf::Event event;
		while (myRawWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				myRawWindow->close();
		}

		myRawWindow->clear({ 120, 120, 120 });

		// OnRender
		Window::OnRender(myRawWindow);
		OnRender(myRawWindow);

		myRawWindow->display();
	}
}

void Window::OnStart()
{

}

void Window::OnUpdate()
{
	Keyboard::UpdateKeyStates();
}

void Window::OnRender(sf::RenderWindow* aWindow)
{

}

void Window::DrawQuad(const int& aWidth, const int& aHeight, const sf::Vector2f& aPosition, const sf::Color& aColor) const
{
	sf::RectangleShape tempQuad({ static_cast<float>(aWidth), static_cast<float>(aHeight) });
	tempQuad.setPosition(aPosition);
	tempQuad.setFillColor(aColor);

	myRawWindow->draw(tempQuad);
}

void Window::DrawCircle(const int& aDiameter, const sf::Vector2f& aPosition, const sf::Color& aColor) const
{
	sf::CircleShape tempCircle(aDiameter / 2);
	tempCircle.setPosition(aPosition);
	tempCircle.setFillColor(aColor);

	myRawWindow->draw(tempCircle);
}

void Window::DrawLine(const sf::Vector2f& aStartPoint, const sf::Vector2f& anEndPoint, const sf::Color& aColor, const int& someLineThickness) const
{
	sf::RectangleShape tempLine{};

	//float tempHypotenuse = sqrt(pow(anEndPoint.x - aStartPoint.x, 2) + pow(anEndPoint.y - aStartPoint.y, 2));
	int tempDeltaX = anEndPoint.x - aStartPoint.x;
	int tempDeltaY = anEndPoint.y - aStartPoint.y;

	sf::Vector2f tempDirection = { static_cast<float>(tempDeltaX), static_cast<float>(tempDeltaY) };
	float tempLength = sqrt(tempDirection.x * tempDirection.x + tempDirection.y * tempDirection.y);

	sf::Vector2f tempNormalizedDirection = tempDirection / tempLength;

	float tempAngle = Math::ToDegrees(asin(tempNormalizedDirection.y));

	// In the case of quadrant 1, do nothing
	// Quadrant 2 and 3
	if (tempDirection.x < 0)
	{
		tempAngle = 180 - tempAngle;
	}
	// Quadrant 4
	else if (tempDirection.x > 0 && tempDirection.y < 0)
	{
		tempAngle = 360 + tempAngle;
	}

	tempLine.setSize({ tempLength, (float)someLineThickness });
	tempLine.setRotation(tempAngle);
	tempLine.setPosition(aStartPoint);
	tempLine.setFillColor(aColor);

	myRawWindow->draw(tempLine);
}

void Window::DrawLine(const sf::Vector2f& aStartPoint, const float& anAngle, const int& aLength, const sf::Color& aColor) const
{
	sf::Vector2f tempDirection = { cos(anAngle), sin(anAngle) };
	sf::Vector2f tempEndPoint = tempDirection * (float)aLength;

	sf::RectangleShape tempLine{};
	tempLine.setSize({ (float)aLength, 1 });
	tempLine.setRotation(Math::ToDegrees(-anAngle));
	tempLine.setPosition(aStartPoint);
	tempLine.setFillColor(aColor);

	myRawWindow->draw(tempLine);
}

void Window::DrawVerticalLine(const sf::Vector2f& aStartPoint, const int& aWidth, const int& aHeight, const sf::Color& aColor)
{
	myPixel.setPosition(aStartPoint);
	myPixel.setScale(aWidth, aHeight);
	myPixel.setFillColor(aColor);

	myRawWindow->draw(myPixel);
}

Window* Window::CurrentWindow = nullptr;
