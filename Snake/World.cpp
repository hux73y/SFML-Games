#include "World.h"

World::World(sf::Vector2u windSize)
{
	blockSize = 16;

	windowSize = windSize;
	respawnApple();
	apple.setFillColor(sf::Color::Red);
	apple.setRadius(blockSize / 2);

	for (int i = 0; i < 4; i++)
	{
		bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2))
			bounds[i].setSize(sf::Vector2f(windowSize.x, blockSize));
		else
			bounds[i].setSize(sf::Vector2f(blockSize, windowSize.y));

		if (i < 2)
			bounds[i].setPosition(0, 0);
		else
		{
			bounds[i].setOrigin(bounds[i].getSize());
			bounds[i].setPosition(sf::Vector2f(windowSize));
		}

	}
}

World::~World() {}

void World::respawnApple()
{
	int maxX = (windowSize.x / blockSize) - 2;
	int maxY = (windowSize.y / blockSize) - 2;
	item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	apple.setPosition(item.x * blockSize, item.y * blockSize);
}

void World::update(Snake& player)
{
	if (player.getPosition() == item)
	{
		player.extend();
		player.increaseScore();
		respawnApple();
	}

	int gridSizeX = windowSize.x / blockSize;
	int gridSizeY = windowSize.y / blockSize;

	if (player.getPosition().x <= 0 || player.getPosition().y <= 0 || player.getPosition().x >= gridSizeX - 1 || player.getPosition().y >= gridSizeY - 1)
		player.lose();
}

void World::render(sf::RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
		window.draw(bounds[i]);

	window.draw(apple);
}

int World::getBlockSize() { return blockSize; }