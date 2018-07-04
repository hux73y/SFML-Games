#include <SFML/Graphics.hpp>
#include <vector>
struct Brick
{
	Brick() {}
	Brick(int x, int y) :position(x, y) {}
	void setPosition(int x, int y);
	sf::Vector2i position;
};

class Form
{
public:
	Form() {};
	void moveDown();
	void moveLeft();
	void moveRight();
	void render(sf::RenderWindow& window, int size);
	void setBricks(int x, int y, int x2, int y2, int x3, int y3, int x4, int y4);
	Brick* getBricks();
	virtual sf::RectangleShape* getRect();
	virtual void setStart(int x, int y);
	virtual void setCurrent();
	virtual void setNext();
	virtual void rotate();
	virtual bool checkRotation(int x, int y);
	virtual std::vector<Brick> posToCheck();
	sf::Texture getTex();
protected:
	Brick bricks[4];
	sf::Color color;
	sf::RectangleShape rect;
	sf::Texture texture;
};

class Line : public Form
{
public:
	Line(int size,sf::Texture);
	~Line() {};

	void rotateDo();
	void rotateLe();
	void rotate();
	bool checkRotation(int x, int y);
	std::vector<Brick> posToCheck();
	void setStart(int x, int y);
	void setCurrent();
	void setNext();
	sf::RectangleShape* getRect();
};

class Cube : public Form
{
public:
	Cube(int size,sf::Texture);
	~Cube() {};

	void setStart(int x, int y);
	void setNext();
	void setCurrent();
	sf::RectangleShape* getRect();
};

class El : public Form
{
public:
	El(int size,sf::Texture);
	~El() {};

	void setStart(int x, int y);
	void setCurrent();
	void setNext();
	void rotateDo();
	void rotateLe();
	void rotateUp();
	void rotateRi();
	void rotate();
	bool checkRotation(int x, int y);
	std::vector<Brick> posToCheck();
	sf::RectangleShape* getRect();
};

class Te : public Form
{
public:
	Te(int size,sf::Texture);
	~Te() {};

	void setStart(int x, int y);
	void setCurrent();
	void setNext();
	void rotateDo();
	void rotateLe();
	void rotateUp();
	void rotateRi();
	void rotate();
	bool checkRotation(int x, int y);
	std::vector<Brick> posToCheck();
	sf::RectangleShape* getRect();
};

class Zet : public Form
{
public:
	Zet(int size,sf::Texture);
	~Zet() {};

	void setStart(int x, int y);
	void setCurrent();
	void setNext();
	void rotateDo();
	void rotateLe();
	void rotate();
	bool checkRotation(int x, int y);
	std::vector<Brick> posToCheck();
	sf::RectangleShape* getRect();
};