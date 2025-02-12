#include "textureHolder.h"
#include <SFML/Graphics/Texture.hpp>
#include<assert.h>
textureHolder* textureHolder::m_s_Instance = nullptr;

textureHolder::textureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& textureHolder::getTexture(std::string const& filename)
{
	auto& m = m_s_Instance->m_textures;
	auto keyvaluePair = m.find(filename);
	if(keyvaluePair != m.end())
	{
		return keyvaluePair->second;
	}
	else
	{
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}
