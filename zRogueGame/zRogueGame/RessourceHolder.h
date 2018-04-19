#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <map>
#include <utility>

/**
* \file			RessourceHolder.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe qui permet de gérer le chargement des textures et des polices de caractères
*
* \details		Classe qui permet de gérer le chargement des textures et des polices de caractères
*
*/


/*! \class		RessourceHolder
* \brief		Classe qui permet de gérer le chargement des textures et des polices de caractères
*
* \details		Classe qui permet de gérer le chargement des textures et des polices de caractères
*
*/

class RessourceHolder
{
public:
	void					loadTexture(std::string textureName, std::string filename);
	sf::Texture&			getTexture(std::string textureName);

	void					loadFont(std::string fontName, std::string filename);
	sf::Font&				getFont(std::string fontName);

private:
	std::map<std::string, sf::Texture> mTextureMap;/*!< */
	std::map<std::string, sf::Font> mFontMap;/*!< */
};

