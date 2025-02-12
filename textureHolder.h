#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <string>
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H
#include<SFML/Graphics.hpp>
#include<map>

class textureHolder
{
	std::map <std::string , sf::Texture> m_textures;
	static textureHolder* m_s_Instance;

	public:
	textureHolder();
	static sf::Texture& getTexture(std::string const& filename);

};


#endif
