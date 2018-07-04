#include "Game.h"
#include <iostream>
Game::Game() : window("Tetris", sf::Vector2u(800, 600)), world(20, 15, 5) // 20
{
	//music.openFromFile("Sounds/theme.ogg");
	setCallbacks();
	//music.play();
	//music.setLoop(true);
}

Game::~Game() {}

void Game::update()
{
	window.update(); // update window events
	float timestep = 1.0f / world.getSpeed();
	if (elapsed.asSeconds() >= timestep)
	{
		world.tick();
		elapsed -= sf::seconds(timestep);
	}
}

void Game::setCallbacks()
{
	window.getEventManager()->addCallback("Move_left", &Cage::moveLeft, world.getCage());
	window.getEventManager()->addCallback("Move_right", &Cage::moveRight, world.getCage());
	window.getEventManager()->addCallback("Move_down", &Cage::moveDown, world.getCage());
	window.getEventManager()->addCallback("rotate", &Cage::rotate, world.getCage());
}

void Game::render()
{
	window.beginDraw(); // clear
	world.render(*window.getRenderWindow());
	window.endDraw(); // display
}

Window* Game::getWindow()
{
	return &window;
}

sf::Time Game::getElapsed()
{
	return elapsed;
}
void Game::restartClock()
{
	elapsed += clock.restart();
}


















