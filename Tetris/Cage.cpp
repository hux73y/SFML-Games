#include "Cage.h"

Cage::Cage(int size, int x, int y) : formManager(size)
{
	posX = x;
	posY = y;
	setup(size, x, y);
}

void Cage::setup(int size, int x, int y)
{
	lost = false;
	score = 0;
	level = 1;
	backGround.setPosition((x * size), (y * size)); 
	backGround.setFillColor(sf::Color(255,255,255,128));
	backGround.setSize(sf::Vector2f(10 * (size), 20 * (size))); 
	backGround.setOutlineThickness(5);
	backGround.setOutlineColor(sf::Color(224, 224, 224));
	rect.setSize(sf::Vector2f(size, size));
	setCageBricks(x, y);
	setFilled();
}

void Cage::render(sf::RenderWindow & win,int size)
{
	win.draw(backGround);
	for(int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
		{
			if (cageBricks[i][j].isFilled)
			{
				rect.setPosition(cageBricks[i][j].brick.position.x * size, cageBricks[i][j].brick.position.y * size);
				rect.setTexture(&cageBricks[i][j].texture);
				win.draw(rect);
			}
		}
	formManager.getCurrent()->render(win,size);
}
bool Cage::checkLost()
{
	for (int i = 0; i < 4; i++)
	{
		if (formManager.getCurrent()->getBricks()[i].position.y <= 5)
		{
			lost = true;
			return true;
		}
	}
	return false;
}
void Cage::insertPositions(Form * form)
{
	int temp, temp2;
	for (int i = 0; i < 4; i++)
	{
		temp = form->getBricks()[i].position.y - 5;
		temp2 = form->getBricks()[i].position.x - 15;
		cageBricks[temp][temp2].texture = form->getTex();
		cageBricks[temp][temp2].isFilled = true;
	}

}

bool Cage::checkCollision()
{
	int temp, temp2;
	for (int i = 0; i < 4; i++)
	{
		temp = formManager.getCurrent()->getBricks()[i].position.y - 5;
		temp2 = formManager.getCurrent()->getBricks()[i].position.x - 15;
		if (temp >= -1)
		if (cageBricks[temp+1][temp2].isFilled || formManager.getCurrent()->getBricks()[i].position.y == 24)
		{
			if (checkLost())
				return true;
			else
			{
				insertPositions(formManager.getCurrent());
				return true;
			}

		}
	}
	return false;
}

void Cage::setCageBricks(int x, int y)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cageBricks[i][j].brick.setPosition(x + j, y + i);
		}
	}
}

bool Cage::checkCollBrick(Form * form, CageBrick &brick)
{
	for (int i = 0; i < 4; i++)
		if (form->getBricks()[i].position.x == brick.brick.position.x && form->getBricks()[i].position.y == brick.brick.position.y + 1)
			return true;
	
	return false;
}

bool Cage::hasLost()
{
	return lost;
}

bool Cage::checkCollGround(Form * form)
{
	for (int i = 0; i < 4; i++)
		if (form->getBricks()[i].position.y == 24)
			return true;

	return false;
}

void Cage::setFilled()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 10; j++)
			cageBricks[i][j].isFilled = false;
}

void Cage::moveLines(int c)
{
	for(int i = c; i > 0; i--)
		for (int j = 0; j < 10; j++)
		{
			cageBricks[i][j].isFilled = cageBricks[i - 1][j].isFilled;
			cageBricks[i][j].texture = cageBricks[i - 1][j].texture;
		}
}

void Cage::deleteLine(int i)
{
	for (int j = 0; j < 10; j++)
	{
		cageBricks[i][j].isFilled = false;
	}
}

void Cage::checkLines()
{
	int i = 19, count = 0;
	while (i > 0)
	{
		if (checkLine(i))
		{
			deleteLine(i);
			moveLines(i);
			count++;
		}
		else
			i--;
	}
	if (count > 0)
		updateScore(count);
}

bool Cage::checkLine(int i)
{
	for (int j = 0; j < 10; j++)
		if (!cageBricks[i][j].isFilled)
			return false;
	
	return true;
}

void Cage::moveLeft(EventDetails * details)
{
	if(checkLeft())
	 formManager.getCurrent()->moveLeft();
}

bool Cage::checkLeft()
{
	int temp,temp2; 
	for (int i = 0; i < 4; i++)
	{ 
		temp = formManager.getCurrent()->getBricks()[i].position.y - 5;
		temp2 =  formManager.getCurrent()->getBricks()[i].position.x - 15;
		if (temp2 <= 0 || temp < 0)
			return false;
		else if (cageBricks[temp][temp2 - 1].isFilled)
			return false;
	}
	return true;
}

void Cage::moveRight(EventDetails * details)
{
	if (checkRight())
		formManager.getCurrent()->moveRight();
}

bool Cage::checkRight()
{
	int temp, temp2;
	for (int i = 0; i < 4; i++)
	{
		temp = formManager.getCurrent()->getBricks()[i].position.y - 5;
		temp2 = formManager.getCurrent()->getBricks()[i].position.x - 15;
		if (temp2 == 9 || temp < 0)
			return false;
		else if (cageBricks[temp][temp2 + 1].isFilled)
			return false;
	}
	return true;
}

void Cage::moveDown(EventDetails * details)
{
	moDo();
}

void Cage::moDo()
{
	if (checkCollision())
	{
		if (lost)
			return;
		else
		{
			checkLines();
			formManager.takeNext();
		}
	}
	else
		formManager.getCurrent()->moveDown();
}

bool Cage::checkRotation()
{
	std::vector<Brick> pos;
	if (formManager.getCurrent()->checkRotation(posX, posY))
	{
		pos = formManager.getCurrent()->posToCheck();
		if (checkPos(pos))
			return true;
	}
	
	return false;
}

bool Cage::checkPos(std::vector<Brick> pos)
{
	for (int i = 0; i < pos.size(); i++)
		if (cageBricks[pos[i].position.y - posY][pos[i].position.x - posX].isFilled)
			return false;

	return true;
}

void Cage::rotate(EventDetails * details)
{
	if(checkRotation())
		formManager.getCurrent()->rotate();
}

void Cage::cleanUp()
{
	delete formManager.getCurrent();
	delete formManager.getNext();
}

FormManager * Cage::getFormManager()
{
	return &formManager;
}

void Cage::setForms()
{
	formManager.setForms();
}

void Cage::updateScore(int count)
{
	switch (count)
	{
	case 1:
		score += 40 * level;
		break;
	case 2:
		score += 100 * level;
		break;
	case 3:
		score += 300 * level;
		break;
	case 4:
		score += 1200 * level;
		break;
	}
}

bool Cage::updateLevel()
{
	if (score >= level * 1000 && level < 99)
	{
		level++;
		return true;
	}

	return false;
}

int Cage::getScore()
{
	return score;
}

int Cage::getLevel()
{
	return level;
}


