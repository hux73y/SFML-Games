#include "Window.h"
#include <iostream>
//#include <SFML/Audio.hpp>
class Game
{
public:
	Game();
	~Game();

	void setCallbacks();
	void update();
	void render();
	Window* getWindow();
	sf::Time getElapsed();
	void restartClock();

private:

	Window window;
	World world;
	//sf::Music music;
	sf::Clock clock;
	sf::Time elapsed;
};


