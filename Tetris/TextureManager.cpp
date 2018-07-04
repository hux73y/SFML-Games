#include "TextureManager.h"

TextureManager::TextureManager()
{
	loadTextures();
}

void TextureManager::loadTextures()
{
	sf::Texture texture;
	texture.loadFromFile("Textures/blue.png");
	textures.push_back(texture);
	texture.loadFromFile("Textures/red.png");
	textures.push_back(texture);
	texture.loadFromFile("Textures/green.png");
	textures.push_back(texture);
	texture.loadFromFile("Textures/yellow.png");
	textures.push_back(texture);
	texture.loadFromFile("Textures/magenta.png");
	textures.push_back(texture);
	texture.loadFromFile("Textures/blue.png");
}

textureContainer* TextureManager::getTexture()
{
	return &textures;
}


