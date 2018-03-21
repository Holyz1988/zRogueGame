#include "RessourceHolder.h"

//Charge une texture
void RessourceHolder::loadTexture(std::string  textureName, const std::string filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename))
	{
		throw std::runtime_error("TextureHolder::Load - Failed to load " + filename);
	}

	mTextureMap.insert(std::pair<std::string, sf::Texture>(textureName, texture));
}

sf::Texture & RessourceHolder::getTexture(std::string  textureName)
{
	auto found = mTextureMap.find(textureName);
	return found->second;
}

void RessourceHolder::loadFont(std::string  fontName, std::string  filename)
{
	sf::Font font;
	if (!font.loadFromFile(filename))
	{
		throw std::runtime_error("FontHolder::Load - Failed to load " + filename);
	}

	mFontMap.insert(std::pair<std::string, sf::Font>(fontName, font));
}

sf::Font & RessourceHolder::getFont(std::string  fontName)
{
	auto found = mFontMap.find(fontName);
	return found->second;
}
