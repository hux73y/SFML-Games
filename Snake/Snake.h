#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

using snakeContainer = std::vector<SnakeSegment>;

enum class Direction { None, Up, Down, Left, Right };

class Snake
{
public:
	Snake(int blockSize);
	~Snake();

	//helper methods
	void setDirection(Direction d);
	Direction getDirection();
	Direction getPhysicalDirection();
	int getSpeed();
	sf::Vector2i getPosition();
	int getLives();
	int getScore();
	void increaseScore();
	bool hasLost();

	void lose(); //handle loosing here
	void toggleLost();

	void extend(); // grow the snake
	void reset(); // reset to start position
	void move(); // movement method
	void tick(); // update method
	void cut(int segment); // method for cutting
	void render(sf::RenderWindow& window);

private:
	void checkCollision(); // checking for collisions

	snakeContainer snakeBody; // vector container of snake segments
	int size; // size of the graphics
	Direction dir; // current direction
	int speed;
	int lives;
	int score;
	bool lost;
	sf::RectangleShape bodyRect;
};