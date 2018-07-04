#include "Window.h"

Window::Window()
{
	setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& title, const sf::Vector2u& size)
{
	setup(title, size);
}

Window::~Window()
{
	destroy();
}

void Window::setup(const std::string& title, const sf::Vector2u& size)
{
	windowTitle = title;
	windowSize = size;
	_isFullscreen = false;
	_isDone = false;
	_isFocused = true;
	eventManager.addCallback("Fullscreen_toggle", &Window::toggleFullscreen, this);
	eventManager.addCallback("Window_close", &Window::close, this);
	create();
}

void Window::create()
{
	auto style = (_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	window.create({ windowSize.x, windowSize.y, 32 }, windowTitle, style);
}

void Window::destroy()
{
	window.close();
}

void Window::update()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus)
		{
			_isFocused = false;
			eventManager.setFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			_isFocused = true;
			eventManager.setFocus(true);
		}
		eventManager.handleEvent(event);
	}
	eventManager.update();
}

void Window::toggleFullscreen(EventDetails* details)
{
	_isFullscreen = !_isFullscreen;
	destroy();
	create();
}

void Window::beginDraw()
{
	window.clear(sf::Color::Black);
}

void Window::endDraw()
{
	window.display();
}

bool Window::isDone()
{
	return _isDone;
}

bool Window::isFullscreen()
{
	return _isFullscreen;
}

sf::Vector2u Window::getWindowSize()
{
	return windowSize;
}

void Window::draw(sf::Drawable& drawable)
{
	window.draw(drawable);
}

sf::RenderWindow * Window::getRenderWindow()
{
	return &window;
}

void Window::close(EventDetails* details)
{
	_isDone = true;
}






