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

	/**
	* \brief	Charge une texture dans le contenaire de texture
	*
	*Charge une texture dans le contenaire de texture
	*
	* \param textureName : chaine de caractère représentant le nom de la texture
	* \param filename : nom du fichier de la texture
	*/
	void					loadTexture(std::string textureName, std::string filename);

	/**
	* \brief	Charge une texture du contenaire de texture
	*
	*Charge une texture du contenaire de texture
	*
	* \param textureName : chaine de caractère représentant le nom de la texture
	*
	* \return référence vers la texture demandé
	*/
	sf::Texture&			getTexture(std::string textureName);

	/**
	* \brief	Charge une texture dans le contenaire de fonts
	*
	*Charge une texture dans le contenaire de fonts
	*
	* \param fontName : chaine de caractère représentant le nom de la font
	* \param filename : nom du fichier de la font
	*
	*/
	void					loadFont(std::string fontName, std::string filename);

	/**
	* \brief	Charge une texture du contenaire de font
	*
	*Charge une texture du contenaire de font
	*
	* \param fontName : chaine de caractère représentant le nom de la font
	*
	* \return référence vers la font demandé
	*/
	sf::Font&				getFont(std::string fontName);

private:
	std::map<std::string, sf::Texture> mTextureMap;/*!< contenaire stockant les textures du jeu*/
	std::map<std::string, sf::Font> mFontMap;/*!< contenaire stockant les polices du jeu*/
};

