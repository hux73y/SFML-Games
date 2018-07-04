#include <SFML/Graphics.hpp>
#include <vector>

typedef std::vector<sf::Texture> textureContainer;

class TextureManager
{
public:
	TextureManager();

	void loadTextures();
	textureContainer* getTexture();
protected:
	textureContainer textures;
};
