#include "Cage.h"
class World
{
public:

	World(int size, int stX, int stY);
	~World() {};

	void setup(int size, int stX, int stY);
	void render(sf::RenderWindow& win);
	void tick();
	void reset();
	void update();
	int getSpeed();
	int getSize();
	//FormManager* getFormMan();
	Cage* getCage();
private:
	//FormManager fman;
	Cage cage;
	sf::RectangleShape background;
	sf::RectangleShape nextBox;
	sf::RectangleShape scoreBox;
	sf::RectangleShape lvlBox;
	sf::Text scoreText;
	sf::Text lvlText;
	sf::Font font;
	sf::Texture texture;
	int brickSize;
	double speed;
	int startX, startY;
};

