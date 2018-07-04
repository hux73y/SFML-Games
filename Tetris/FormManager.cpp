#include "FormManager.h"

FormManager::FormManager(int size)
{
	std::srand(std::time(nullptr));
}

void FormManager::render(sf::RenderWindow & window, int size)
{
	next->render(window, size);
	current->render(window, size);
}

void FormManager::setForms()
{
	pickForm();
	current = next;
	current->setCurrent();
	pickForm();
}

void FormManager::pickForm()
{
	int randInt = (std::rand() % 5);
	switch (randInt)
	{
	case 0:
		next = new Line(20,texMan.getTexture()->at(0));
		next->setNext();
		break;
	case 1:
		next = new Cube(20,texMan.getTexture()->at(1));
		next->setNext();
		break;
	case 2:
		next = new El(20, texMan.getTexture()->at(2));
		next->setNext();
		break;
	case 3:
		next = new Te(20, texMan.getTexture()->at(3));
		next->setNext();
		break;
	case 4:
		next = new Zet(20, texMan.getTexture()->at(4));
		next->setNext();
		break;
	}

}

void FormManager::takeNext()
{
	delete current;
	current = next;
	current->setCurrent();
	pickForm();
}

Form * FormManager::getNext()
{
	return next;
}

Form * FormManager::getCurrent()
{
	return current;
}
