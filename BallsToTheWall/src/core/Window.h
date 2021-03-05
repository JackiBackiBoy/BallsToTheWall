#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "SFML/Graphics.hpp"
#include <string>

class Window
{
public:
	Window(const std::string& aTitle, const int& aWidth, const int& aHeight) : myTitle(aTitle), myWidth(aWidth), myHeight(aHeight) {};
	~Window() {};

	void Run();

	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender(sf::RenderWindow* aWindow) = 0;

	void DrawQuad(const int& aWidth, const int& aHeight, const sf::Vector2f& aPosition, const sf::Color& aColor) const;
	void DrawCircle(const int& aDiameter, const sf::Vector2f& aPosition, const sf::Color& aColor) const;
	void DrawLine(const sf::Vector2f& aStartPoint, const sf::Vector2f& anEndPoint, const sf::Color& aColor, const int& someLineThickness = 1) const;
	void DrawLine(const sf::Vector2f& aStartPoint, const float& anAngle, const int& aLength, const sf::Color& aColor) const;
	void DrawVerticalLine(const sf::Vector2f& aStartPoint, const int& aWidth, const int& aHeight, const sf::Color& aColor);
	sf::Vector2f MouseWorldPos()
	{
		return (sf::Vector2f)GetRawWindow()->mapPixelToCoords((sf::Vector2i)sf::Mouse::getPosition() - GetRawWindow()->getPosition());
	}

	inline sf::RenderWindow* GetRawWindow() const { return myRawWindow; }

	static Window* CurrentWindow;

protected:
	std::string myTitle;
	int myWidth;
	int myHeight;
	sf::RenderWindow* myRawWindow;
	sf::RectangleShape myPixel;
};
#endif