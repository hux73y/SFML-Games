// EventMan.h
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo
{
	EventInfo() { code = 0; }
	EventInfo(int event) { code = event; }
	union
	{
		int code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails
{
	EventDetails(const std::string& bindName) : name(bindName)
	{
		Clear();
	}
	std::string name;
	sf::Vector2i size;
	sf::Uint32 textEntered;
	sf::Vector2i mouse;
	int mouseWheelDelta;
	int keyCode;

	void Clear()
	{
		size = sf::Vector2i(0, 0);
		textEntered = 0;
		mouse = sf::Vector2i(0, 0);
		mouseWheelDelta = 0;
		keyCode = -1;
	}
};

struct Binding
{
	Binding(const std::string& l_name) : name(l_name), details(l_name), c(0) {}
	void BindEvent(EventType type, EventInfo info = EventInfo())
	{
		events.emplace_back(type, info);
	}

	Events events;
	std::string name;
	int c; // Count of events that are "happening"

	EventDetails details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool addBinding(Binding *binding);
	bool removeBinding(std::string name);
	void setFocus(const bool& focus) { hasFocus = focus; }

	template<class T> bool addCallback(const std::string& name, void(T::*func)(EventDetails*), T* instance)
	{
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return callbacks.emplace(name, temp).second;
	}

	void removeCallback(const std::string name) { callbacks.erase(name); };
	void handleEvent(sf::Event& event);
	void update();

	sf::Vector2i getMousePos(sf::RenderWindow* wind = nullptr)
	{
		return (wind ? sf::Mouse::getPosition(*wind) : sf::Mouse::getPosition());
	}
private:
	void loadBindings();
	Bindings bindings;
	Callbacks callbacks;
	bool hasFocus;
};




















