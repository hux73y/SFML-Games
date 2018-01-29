#include "Game.h"

Game::Game() : window("Snake", sf::Vector2u(800, 600)), snake(world.getBlockSize()), world(sf::Vector2u(800, 600))
{
	textbox.setup(5, 14, 350, sf::Vector2f(255, 0));
	textbox.add("seed random number generator with: " + std::to_string(time(NULL)));
}

Game::~Game() {}

void Game::update()
{
	window.update(); // update window events

	float timestep = 1.0f / snake.getSpeed();
	if (elapsed.asSeconds() >= timestep)
	{
		snake.tick();
		world.update(snake);
		elapsed -= sf::seconds(timestep);
		if (snake.hasLost())
		{
			textbox.add("Game Over! Score: " + std::to_string(snake.getScore()));
			snake.reset();
		}
			
	}

}

void Game::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.getPhysicalDirection() != Direction::Down)
		snake.setDirection(Direction::Up);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.getPhysicalDirection() != Direction::Up)
		snake.setDirection(Direction::Down);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.getPhysicalDirection() != Direction::Right)
		snake.setDirection(Direction::Left);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.getPhysicalDirection() != Direction::Left)
		snake.setDirection(Direction::Right);
	
		
}

void Game::render()
{
	window.beginDraw(); // clear
	world.render(*window.getRenderWindow());
	snake.render(*window.getRenderWindow());
	textbox.render(*window.getRenderWindow());
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


















