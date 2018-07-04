#include "Form.h"
#include <iostream>
void Brick::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void Form::moveDown()
{
	bricks[0].position.y++;
	bricks[1].position.y++;
	bricks[2].position.y++;
	bricks[3].position.y++;
}

void Form::moveLeft()
{
	bricks[0].position.x--;
	bricks[1].position.x--;
	bricks[2].position.x--;
	bricks[3].position.x--;
}

void Form::moveRight()
{

	bricks[0].position.x++;
	bricks[1].position.x++;
	bricks[2].position.x++;
	bricks[3].position.x++;

}

void Form::render(sf::RenderWindow& win, int size)
{
	for (int i = 0; i < 4; i++)
	{
		rect.setPosition(bricks[i].position.x * size, bricks[i].position.y * size);
		win.draw(rect);
	}
}

void Form::setBricks(int x, int y, int x2, int y2, int x3, int y3, int x4, int y4)
{
	bricks[0].setPosition(x, y);
	bricks[1].setPosition(x2, y2);
	bricks[2].setPosition(x3, y3);
	bricks[3].setPosition(x4, y4);
}

Brick* Form::getBricks()
{
	return bricks;
}

sf::RectangleShape * Form::getRect()
{
	return &rect;
}

void Form::setStart(int x, int y)
{
}

void Form::setCurrent()
{
}

void Form::setNext()
{
}

void Form::rotate()
{
}

bool Form::checkRotation(int x, int x2)
{
	return true;
}

std::vector<Brick> Form::posToCheck()
{
	return std::vector<Brick>();
}

sf::Texture Form::getTex()
{
	return texture;
}

/*Line Functions*/

Line::Line(int size,sf::Texture tex)
{
	rect.setSize(sf::Vector2f(size, size));
	texture = tex;
	rect.setTexture(&texture);
}

void Line::rotateDo()
{
	bricks[0].setPosition(bricks[0].position.x + 2, bricks[0].position.y - 2);
	bricks[1].setPosition(bricks[1].position.x + 1, bricks[1].position.y - 1);
	bricks[3].setPosition(bricks[3].position.x - 1, bricks[3].position.y + 1);
}
void Line::rotateLe()
{
	bricks[0].setPosition(bricks[0].position.x - 2, bricks[0].position.y + 2);
	bricks[1].setPosition(bricks[1].position.x - 1, bricks[1].position.y + 1);
	bricks[3].setPosition(bricks[3].position.x + 1, bricks[3].position.y - 1);
}

void Line::rotate()
{
	if (bricks[1].position.y == bricks[2].position.y)
		rotateDo();
	else
		rotateLe();
}


bool Line::checkRotation(int x, int y)
{
	if (bricks[0].position.y == bricks[1].position.y)
		return (bricks[0].position.y >= y + 2) && (bricks[0].position.y < y + 19);
	else
		return ((bricks[0].position.x >= x + 2) && (bricks[1].position.x <= x + 8));
}

std::vector<Brick> Line::posToCheck()
{
	std::vector<Brick> pos;
	if (bricks[0].position.y == bricks[1].position.y)
	{
		pos.push_back(Brick(bricks[0].position.x, bricks[0].position.y - 1));
		pos.push_back(Brick(bricks[0].position.x, bricks[0].position.y - 2));
		pos.push_back(Brick(bricks[1].position.x, bricks[1].position.y - 1));
		pos.push_back(Brick(bricks[1].position.x, bricks[1].position.y - 2));
		pos.push_back(Brick(bricks[2].position.x, bricks[2].position.y - 1));
		pos.push_back(Brick(bricks[2].position.x, bricks[2].position.y - 2));
		pos.push_back(Brick(bricks[2].position.x, bricks[2].position.y + 1));
		pos.push_back(Brick(bricks[3].position.x, bricks[3].position.y + 1));
	}
	else
	{
		pos.push_back(Brick(bricks[0].position.x - 1, bricks[0].position.y));
		pos.push_back(Brick(bricks[0].position.x - 2, bricks[0].position.y));
		pos.push_back(Brick(bricks[1].position.x - 1, bricks[1].position.y));
		pos.push_back(Brick(bricks[1].position.x - 2, bricks[1].position.y));
		pos.push_back(Brick(bricks[2].position.x - 1, bricks[2].position.y));
		pos.push_back(Brick(bricks[2].position.x - 2, bricks[2].position.y));
		pos.push_back(Brick(bricks[2].position.x + 1, bricks[2].position.y));
		pos.push_back(Brick(bricks[3].position.x + 1, bricks[3].position.y));
	}
	return pos;

}

void Line::setStart(int x, int y)
{
	setBricks(x, y, x + 1, y, x + 2, y, x + 3, y);
}

void Line::setCurrent()
{
	setStart(18, 5);
}

void Line::setNext()
{
	setStart(30, 6);
}

sf::RectangleShape * Line::getRect()
{
	return &rect;
}

/*Cube Functions*/

Cube::Cube(int size,sf::Texture tex)
{
	rect.setSize(sf::Vector2f(size, size));
	texture = tex;
	rect.setTexture(&texture);
}

/*El Functions*/

El::El(int size, sf::Texture tex)
{
	rect.setSize(sf::Vector2f(size, size));
	texture = tex;
	rect.setTexture(&texture);
}

void El::setStart(int x, int y)
{
	setBricks(x, y, x + 1, y, x + 2, y, x + 2, y - 1);
}

void El::setCurrent()
{
	setStart(18, 6);
}

void El::setNext()
{
	setStart(30, 7);
}

void El::rotateDo()
{
	bricks[0].setPosition(bricks[0].position.x + 1, bricks[0].position.y - 1);
	bricks[2].setPosition(bricks[2].position.x - 1, bricks[2].position.y + 1);
	bricks[3].setPosition(bricks[3].position.x, bricks[3].position.y + 2);
}

void El::rotateLe()
{
	bricks[0].setPosition(bricks[0].position.x + 1, bricks[0].position.y + 1);
	bricks[2].setPosition(bricks[2].position.x - 1, bricks[2].position.y - 1);
	bricks[3].setPosition(bricks[3].position.x - 2, bricks[3].position.y);

}

void El::rotateUp()
{
	bricks[0].setPosition(bricks[0].position.x - 1, bricks[0].position.y + 1);
	bricks[2].setPosition(bricks[2].position.x + 1, bricks[2].position.y - 1);
	bricks[3].setPosition(bricks[3].position.x, bricks[3].position.y - 2);

}

void El::rotateRi()
{
	bricks[0].setPosition(bricks[0].position.x - 1, bricks[0].position.y - 1);
	bricks[2].setPosition(bricks[2].position.x + 1, bricks[2].position.y + 1);
	bricks[3].setPosition(bricks[3].position.x + 2, bricks[3].position.y);

}

void El::rotate()
{
	if (bricks[1].position.y == bricks[2].position.y)
	{
		if (bricks[1].position.x < bricks[2].position.x)
			rotateDo();
		else
			rotateUp();
	}
	else
	{
		if (bricks[1].position.y < bricks[2].position.y)
			rotateLe();
		else
			rotateRi();
	}
}

bool El::checkRotation(int x, int y)
{
	if (bricks[0].position.y == bricks[1].position.y)
		return (bricks[3].position.y >= y) && (bricks[0].position.y < y + 19);
	else
		return ((bricks[0].position.x >= x + 1) && (bricks[0].position.x <= x + 8));
}

std::vector<Brick> El::posToCheck()
{
	std::vector<Brick> pos;
	if (bricks[1].position.y == bricks[2].position.y)
	{
		if (bricks[1].position.x < bricks[2].position.x)
		{
			pos.push_back(Brick(bricks[0].position.x, bricks[0].position.y - 1));
			pos.push_back(Brick(bricks[1].position.x, bricks[1].position.y - 1));
			pos.push_back(Brick(bricks[1].position.x, bricks[1].position.y + 1));
			pos.push_back(Brick(bricks[2].position.x, bricks[2].position.y + 1));
		}
		else
		{
			pos.push_back(Brick(bricks[0].position.x, bricks[0].position.y + 1));
			pos.push_back(Brick(bricks[1].position.x, bricks[1].position.y - 1));
			pos.push_back(Brick(bricks[1].position.x, bricks[1].position.y + 1));
			pos.push_back(Brick(bricks[2].position.x, bricks[2].position.y - 1));
		}
	}
	else
	{
		if (bricks[1].position.y < bricks[2].position.y)
		{
			pos.push_back(Brick(bricks[0].position.x + 1, bricks[0].position.y));
			pos.push_back(Brick(bricks[1].position.x + 1, bricks[1].position.y));
			pos.push_back(Brick(bricks[1].position.x - 1, bricks[1].position.y));
			pos.push_back(Brick(bricks[2].position.x - 1, bricks[2].position.y));
		}
		else
		{
			pos.push_back(Brick(bricks[0].position.x - 1, bricks[0].position.y));
			pos.push_back(Brick(bricks[1].position.x + 1, bricks[1].position.y));
			pos.push_back(Brick(bricks[1].position.x - 1, bricks[1].position.y));
			pos.push_back(Brick(bricks[2].position.x + 1, bricks[2].position.y));
		}
	}
	return pos;
}

sf::RectangleShape * El::getRect()
{
	return &rect;
}

/*Te Functions*/
Te::Te(int size, sf::Texture tex)
{
	rect.setSize(sf::Vector2f(size, size));
	texture = tex;
	rect.setTexture(&texture);
}

void Te::setStart(int x, int y)
{
	setBricks(x, y, x + 1, y - 1, x + 1, y, x + 2, y);
}

void Te::setCurrent()
{
	setStart(18, 6);
}

void Te::setNext()
{
	setStart(30, 7);
}

void Te::rotateDo()
{
	bricks[0].setPosition(bricks[0].position.x + 1, bricks[0].position.y - 1);
	bricks[1].setPosition(bricks[1].position.x + 1, bricks[1].position.y + 1);
	bricks[3].setPosition(bricks[3].position.x - 1, bricks[3].position.y + 1);
}

void Te::rotateLe()
{
	bricks[0].setPosition(bricks[0].position.x + 1, bricks[0].position.y + 1);
	bricks[1].setPosition(bricks[1].position.x - 1, bricks[1].position.y + 1);
	bricks[3].setPosition(bricks[3].position.x - 1, bricks[3].position.y - 1);
}

void Te::rotateUp()
{
	bricks[0].setPosition(bricks[0].position.x - 1, bricks[0].position.y + 1);
	bricks[1].setPosition(bricks[1].position.x - 1, bricks[1].position.y - 1);
	bricks[3].setPosition(bricks[3].position.x + 1, bricks[3].position.y - 1);
}

void Te::rotateRi()
{
	bricks[0].setPosition(bricks[0].position.x - 1, bricks[0].position.y - 1);
	bricks[1].setPosition(bricks[1].position.x + 1, bricks[1].position.y - 1);
	bricks[3].setPosition(bricks[3].position.x + 1, bricks[3].position.y + 1);
}

void Te::rotate()
{
	if (bricks[1].position.x == bricks[2].position.x)
	{
		if (bricks[1].position.y < bricks[2].position.y)
			rotateDo();
		else
			rotateUp();
	}
	else
	{
		if (bricks[2].position.x < bricks[1].position.x)
			rotateLe();
		else
			rotateRi();
	}
}

bool Te::checkRotation(int x, int y)
{
	if (bricks[0].position.y == bricks[2].position.y)
		return bricks[2].position.y < y + 19;
	else
		return ((bricks[2].position.x > x) && (bricks[2].position.x < x + 9));
}

std::vector<Brick> Te::posToCheck()
{
	std::vector<Brick> pos;
	if (bricks[1].position.x == bricks[2].position.x)
	{
		if (bricks[1].position.y < bricks[2].position.y)
		{
			pos.push_back(Brick(bricks[0].position.x, bricks[0].position.y - 1));
			pos.push_back(Brick(bricks[2].position.x, bricks[2].position.y + 1));
			pos.push_back(Brick(bricks[3].position.x, bricks[3].position.y - 1));
			pos.push_back(Brick(bricks[3].position.x, bricks[3].position.y + 1));
		}
		else
		{
			pos.push_back(Brick(bricks[0].position.x, bricks[0].position.y + 1));
			pos.push_back(Brick(bricks[2].position.x, bricks[2].position.y - 1));
			pos.push_back(Brick(bricks[3].position.x, bricks[3].position.y + 1));
			pos.push_back(Brick(bricks[3].position.x, bricks[3].position.y - 1));
		}
	}
	else
	{
		if (bricks[2].position.x < bricks[1].position.x)
		{
			pos.push_back(Brick(bricks[0].position.x + 1, bricks[0].position.y));
			pos.push_back(Brick(bricks[2].position.x - 1, bricks[2].position.y));
			pos.push_back(Brick(bricks[3].position.x + 1, bricks[3].position.y));
			pos.push_back(Brick(bricks[3].position.x - 1, bricks[3].position.y));
		}
		else
		{
			pos.push_back(Brick(bricks[0].position.x - 1, bricks[0].position.y));
			pos.push_back(Brick(bricks[2].position.x + 1, bricks[2].position.y));
			pos.push_back(Brick(bricks[3].position.x - 1, bricks[3].position.y));
			pos.push_back(Brick(bricks[3].position.x + 1, bricks[3].position.y));
		}
	}
	return pos;
}

sf::RectangleShape * Te::getRect()
{
	return &rect;
}

Zet::Zet(int size, sf::Texture tex)
{
	rect.setSize(sf::Vector2f(size, size));
	texture = tex;
	rect.setTexture(&texture);
}

void Zet::setStart(int x, int y)
{
	setBricks(x, y, x + 1, y, x + 1, y + 1, x + 2, y + 1);
}

void Zet::setCurrent()
{
	setStart(18, 5);
}

void Zet::setNext()
{
	setStart(30, 6);
}

void Zet::rotateDo()
{
	bricks[0].setPosition(bricks[0].position.x + 1, bricks[0].position.y - 1);
	bricks[2].setPosition(bricks[2].position.x - 1, bricks[2].position.y - 1);
	bricks[3].setPosition(bricks[3].position.x - 2, bricks[3].position.y);
}

void Zet::rotateLe()
{
	bricks[0].setPosition(bricks[0].position.x - 1, bricks[0].position.y + 1);
	bricks[2].setPosition(bricks[2].position.x + 1, bricks[2].position.y + 1);
	bricks[3].setPosition(bricks[3].position.x + 2, bricks[3].position.y);
}

void Zet::rotate()
{
	if (bricks[1].position.x == bricks[2].position.x)
		rotateDo();
	else
		rotateLe();
}


bool Zet::checkRotation(int x, int y)
{
	return bricks[0].position.x <= x + 8;
}

std::vector<Brick> Zet::posToCheck()
{
	std::vector<Brick> pos;
	if (bricks[1].position.x == bricks[2].position.x)
	{
		pos.push_back(Brick(bricks[0].position.x, bricks[0].position.y - 1));
		pos.push_back(Brick(bricks[0].position.x, bricks[0].position.y + 1));
		pos.push_back(Brick(bricks[1].position.x, bricks[1].position.y - 1));
	}
	else
	{
		pos.push_back(Brick(bricks[0].position.x - 1, bricks[0].position.y));
		pos.push_back(Brick(bricks[3].position.x + 1, bricks[3].position.y));
		pos.push_back(Brick(bricks[3].position.x + 2, bricks[3].position.y));
	}
	return pos;
}

sf::RectangleShape * Zet::getRect()
{
	return &rect;
}

void Cube::setStart(int x, int y)
{
	setBricks(x, y, x + 1, y, x, y + 1, x + 1, y + 1);
}

void Cube::setNext()
{
	setStart(31, 6);
}

void Cube::setCurrent()
{
	setStart(18, 5);
}

sf::RectangleShape * Cube::getRect()
{
	return &rect;
}
