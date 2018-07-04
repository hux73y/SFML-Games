#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "World.h"
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
	bool isFocused() { return _isFocused; };
	EventManager* getEventManager() { return &eventManager; };
	sf::Vector2u getWindowSize();

	void toggleFullscreen(EventDetails* details);
	void close(EventDetails* details);
	void draw(sf::Drawable& drawable);
	sf::RenderWindow* getRenderWindow();

private:
	void setup(const std::string& title, const sf::Vector2u& size);

	void destroy();
	void create();

	sf::RenderWindow window;
	sf::Vector2u windowSize;
	std::string windowTitle;
	EventManager eventManager;

	bool _isFocused;
	bool _isDone;
	bool _isFullscreen;
};



