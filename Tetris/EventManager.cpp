#include "EventManager.h"

EventManager::EventManager() : hasFocus(true) { loadBindings(); }

EventManager::~EventManager()
{
	for (auto &itr : bindings)
	{
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::addBinding(Binding* binding)
{
	if (bindings.find(binding->name) != bindings.end())
		return false;

	return bindings.emplace(binding->name, binding).second;
}

bool EventManager::removeBinding(std::string name)
{
	auto itr = bindings.find(name);
	if (itr == bindings.end())
		return false;

	delete itr->second;
	bindings.erase(itr);
	return true;
}

void EventManager::handleEvent(sf::Event& event)
{
	for (auto &b_itr : bindings)
	{
		Binding* bind = b_itr.second;
		for (auto &e_itr : bind->events)
		{
			EventType sfmlEvent = (EventType)event.type;
			if (e_itr.first != sfmlEvent)
				continue;
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				if (e_itr.second.code == event.key.code)
				{
					if (bind->details.keyCode != -1)
					{
						bind->details.keyCode = e_itr.second.code;
					}
					++(bind->c);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
			{
				if (e_itr.second.code == event.mouseButton.button)
				{
					bind->details.mouse.x = event.mouseButton.x;
					bind->details.mouse.y = event.mouseButton.y;
					if (bind->details.keyCode != -1)
					{
						bind->details.keyCode = e_itr.second.code;
					}
					++(bind->c);
					break;
				}
			}
			else
			{
				if (sfmlEvent == EventType::MouseWheel)
				{
					bind->details.mouseWheelDelta = event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized)
				{
					bind->details.size.x = event.size.width;
					bind->details.size.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered)
				{
					bind->details.textEntered = event.text.unicode;
				}
				++(bind->c);
			}
		}
	}
}

void EventManager::update()
{
	if (!hasFocus) { return; }
	for (auto &b_itr : bindings)
	{
		Binding* bind = b_itr.second;
		for (auto &e_itr : bind->events)
		{
			switch (e_itr.first)
			{
			case(EventType::Keyboard):
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.code)))
				{
					if (bind->details.keyCode != -1)
						bind->details.keyCode = e_itr.second.code;

					++(bind->c);
				}
				break;

			case(EventType::Mouse):
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.code)))
				{
					if (bind->details.keyCode != -1)
						bind->details.keyCode = e_itr.second.code;
					++(bind->c);
				}
				break;

			case(EventType::Joystick):
				break;
			}
		}

		if (bind->events.size() == bind->c)
		{
			auto callItr = callbacks.find(bind->name);
			if (callItr != callbacks.end())
			{
				callItr->second(&bind->details);
			}
		}
		bind->c = 0;
		bind->details.Clear();
	}
}

void EventManager::loadBindings()
{
	std::string delimiter = ":";

	std::ifstream bindingStr;
	bindingStr.open("Key.txt");
	if (!bindingStr.is_open())
	{
		std::cout << "! Failed loading Key.txt" << std::endl;
		return;
	}
	std::string line;
	while (std::getline(bindingStr, line))
	{
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);

		while (!keystream.eof())
		{
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos)
			{
				delete bind;
				bind = nullptr;
				break;
			}
			EventType type = EventType(stoi(keyval.substr(start, end - start)));
			int code = stoi(keyval.substr(end + delimiter.length(), keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo.code = code;

			bind->BindEvent(type, eventInfo);
		}
		if (!addBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindingStr.close();
}



















