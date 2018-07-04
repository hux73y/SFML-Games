#include "Form.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "TextureManager.h"
class FormManager
{
public:
	FormManager(int size);
	~FormManager() {};

	void render(sf::RenderWindow& window, int size);
	void setForms();
	void pickForm();
	void takeNext();
	Form* getNext();
	Form* getCurrent();

private:
	TextureManager texMan;
	Form* current;
	Form* next;
};