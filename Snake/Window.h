#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Window
{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();

	void update();

	bool isDone();
	bool isFullscreen();

	sf::Vector2u getWindowSize();

	void toggleFullscreen();
	void draw(sf::Drawable& drawable);
	sf::RenderWindow* getRenderWindow();

private:
	void setup(const std::string& title, const sf::Vector2u& size);

	void destroy();
	void create();

	sf::RenderWindow window;
	sf::Vector2u windowSize;
	std::string windowTitle;

	bool _isDone;
	bool _isFullscreen;
};

