#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <map>
#include <utility>

class RessourceHolder
{
public:
	void					loadTexture(std::string textureName, std::string filename);
	sf::Texture&			getTexture(std::string textureName);

	void					loadFont(std::string fontName, std::string filename);
	sf::Font&				getFont(std::string fontName);

private:
	std::map<std::string, sf::Texture> mTextureMap;
	std::map<std::string, sf::Font> mFontMap;
};

