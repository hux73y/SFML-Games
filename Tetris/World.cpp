#include "World.h"
#include <iostream>
World::World(int size, int stX, int stY) : cage(size, 15, 5)
{
	setup(size, stX, stY);
}

void World::setup(int size, int stX, int stY)
{
	brickSize = size;
	speed = 1;
	startX = stX;
	startY = stY;
	background.setSize(sf::Vector2f(800, 600));
	texture.loadFromFile("Textures/simpleBlack.jpg");
	background.setTexture(&texture);
	nextBox.setSize(sf::Vector2f(10 * size, 4 * size));
	nextBox.setPosition((stX * size) + (12 * size), (stY * size));
	nextBox.setFillColor(sf::Color(255, 255, 255, 128));
	nextBox.setOutlineThickness(5);
	nextBox.setOutlineColor(sf::Color(224, 224, 224));
	scoreBox.setSize(sf::Vector2f(10 * size, 2 * size));
	scoreBox.setPosition((stX * size) + (12 * size), (stY * size) + (5 * size));
	scoreBox.setFillColor(sf::Color(255, 255, 255, 128));
	scoreBox.setOutlineThickness(5);
	scoreBox.setOutlineColor(sf::Color(224, 224, 224));
	lvlBox.setSize(sf::Vector2f(10 * size, 2 * size));
	lvlBox.setPosition((stX * size) + (12 * size), (stY * size) + (8 * size));
	lvlBox.setFillColor(sf::Color(255, 255, 255, 128));
	lvlBox.setOutlineThickness(5);
	lvlBox.setOutlineColor(sf::Color(224, 224, 224));
	font.loadFromFile("arial.ttf");
	scoreText.setFont(font);
	lvlText.setFont(font);
	scoreText.setCharacterSize(40);
	lvlText.setCharacterSize(40);
	scoreText.setPosition((stX * size) + (12 * size), (stY * size) + (4.75 * size));
	lvlText.setPosition((stX * size) + (12 * size), (stY * size) + (7.75 * size));


	cage.setForms();
}

void World::render(sf::RenderWindow& win)
{
	win.draw(background);
	win.draw(nextBox);
	win.draw(scoreBox);
	win.draw(lvlBox);
	win.draw(scoreText);
	win.draw(lvlText);
	cage.getFormManager()->getNext()->render(win, brickSize);
	cage.render(win, brickSize );
}

void World::tick()
{
	cage.moDo();
	update();
}

void World::reset()
{
	cage.setup(brickSize, startX, startY);
	cage.cleanUp();
	cage.setForms();
}

void World::update()
{
	if(cage.hasLost())
		reset();
	if (cage.updateLevel() && cage.getLevel() <= 22)
		speed += 0.4;

	scoreText.setString(std::to_string(cage.getScore()));
	lvlText.setString(std::to_string(cage.getLevel()));
}

int World::getSpeed()
{
	return speed;
}

int World::getSize()
{
	return brickSize;
}

Cage * World::getCage()
{
	return &cage;
}
