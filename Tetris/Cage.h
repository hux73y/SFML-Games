#include <SFML/Graphics.hpp>
#include "FormManager.h"
#include "EventManager.h"
struct CageBrick
{
	CageBrick() {}
	CageBrick(int x, int y) : brick(x, y) {}

	Brick brick;
	sf::Texture texture;
	bool isFilled = false;
};

class Cage
{
public:
	Cage(int size, int x, int y);
	~Cage() {};

	void setup(int size, int x, int y);
	void render(sf::RenderWindow& win, int size);
	bool checkLost();
	bool checkCollision();
	void insertPositions(Form* form);
	void setCageBricks(int x, int y);
	bool checkCollBrick(Form* form, CageBrick &brick);
	bool hasLost();
	bool checkCollGround(Form* form);
	void setFilled();
	void moveLines(int);
	void deleteLine(int);
	void checkLines();
	bool checkLine(int);
	void moveLeft(EventDetails* details);
	bool checkLeft();
	void moveRight(EventDetails* details);
	bool checkRight();
	void moveDown(EventDetails* details);
	void moDo();
	bool checkRotation();
	bool checkPos(std::vector<Brick>);
	void rotate(EventDetails* details);
	void cleanUp();
	FormManager* getFormManager();
	void setForms();
	void updateScore(int c);
	bool updateLevel();
	int getScore();
	int getLevel();

protected:
	bool lost;
	int posX, posY, score, level;
	FormManager formManager;
	CageBrick cageBricks[20][10];
	Brick collisionLine[10];
	sf::RectangleShape backGround;
	sf::RectangleShape rect;
};


