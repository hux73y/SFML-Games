#include "Snake.h"

Snake::Snake(int blockSize)
{
	size = blockSize;
	bodyRect.setSize(sf::Vector2f(size - 1, size - 1));
	reset();
}

Snake::~Snake() {}

void Snake::reset()
{
	snakeBody.clear();

	//snakeBody.push_back(SnakeSegment(5, 9));
	//snakeBody.push_back(SnakeSegment(5, 8));
	//snakeBody.push_back(SnakeSegment(5, 7));
	//snakeBody.push_back(SnakeSegment(5, 6));
	snakeBody.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None); // start of still
	speed = 15;
	lives = 3;
	score = 0;
	lost = false;
}

void Snake::setDirection(Direction d)
{
	dir = d;
}

Direction Snake::getDirection()
{
	return dir;
}

Direction Snake::getPhysicalDirection()
{
	if (snakeBody.size() <= 1) return Direction::None;
	SnakeSegment& head = snakeBody[0];
	SnakeSegment& neck = snakeBody[1];

	if (head.position.x == neck.position.x)
		return (head.position.y > neck.position.y ? Direction::Down : Direction::Up);
	else if (head.position.y == neck.position.y)
		return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);

	return Direction();
}

int Snake::getSpeed()
{
	return speed;
}

sf::Vector2i Snake::getPosition()
{
	return (!snakeBody.empty() ? snakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::getLives()
{
	return lives;
}

int Snake::getScore()
{
	return score;
}

void Snake::increaseScore()
{
	score += 10;
}

bool Snake::hasLost()
{
	return lost;
}

void Snake::lose()
{
	lost = true;
}

void Snake::toggleLost()
{
	lost = !lost;
}

void Snake::extend()
{
	if (snakeBody.empty()) { return; }
	SnakeSegment& tail_head = snakeBody[snakeBody.size() - 1];

	if (snakeBody.size() > 1)
	{
		SnakeSegment& tail_bone = snakeBody[snakeBody.size() - 2];
		if (tail_head.position.x == tail_bone.position.x)
		{
			if (tail_head.position.y > tail_bone.position.y)
				snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			else
				snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		}
		else if (tail_head.position.y == tail_bone.position.y)
		{
			if (tail_head.position.x > tail_bone.position.x)
				snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			else
				snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
	}
	else
	{
		if (dir == Direction::Up)
			snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		else if (dir == Direction::Down)
			snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		else if (dir == Direction::Left)
			snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		else if (dir == Direction::Right)
			snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
	}
}

void Snake::tick()
{
	if (snakeBody.empty()) { return; }
	if (dir == Direction::None) { return; }
	move();
	checkCollision();
}

void Snake::move()
{
	for (int i = snakeBody.size() - 1; i > 0; --i)
		snakeBody[i].position = snakeBody[i - 1].position;
	if (dir == Direction::Left)
		--snakeBody[0].position.x;
	else if (dir == Direction::Right)
		++snakeBody[0].position.x;
	else if (dir == Direction::Up)
		--snakeBody[0].position.y;
	else if (dir == Direction::Down)
		++snakeBody[0].position.y;
}

void Snake::checkCollision()
{
	if (snakeBody.size() < 5) { return; }
	SnakeSegment& head = snakeBody.front();
	for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr)
	{
		if (itr->position == head.position)
		{
			int segments = snakeBody.end() - itr;
			cut(segments);
			break;
		}
	}
}

void Snake::cut(int segment)
{
	for (int i = 0; i < segment; i++)
		snakeBody.pop_back();
	--lives;
	if (lives == 0) { lose(); return; }
}

void Snake::render(sf::RenderWindow& window)
{
	if (snakeBody.empty()) { return; }
	auto head = snakeBody.begin();
	bodyRect.setFillColor(sf::Color::Yellow);
	bodyRect.setPosition(head->position.x * size, head->position.y * size);
	window.draw(bodyRect);

	bodyRect.setFillColor(sf::Color::Green);
	for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); itr++)
	{
		bodyRect.setPosition(itr->position.x * size, itr->position.y * size);
		window.draw(bodyRect);
	}
}
















