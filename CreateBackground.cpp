#include"ZombieArena.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

int createBackground(sf::VertexArray& rVA , sf::IntRect arena)
{
	const int tileSize = 50;
	const int tileTypes = 3;
	const int verticeNumber = 4;

	int worldWidth = arena.width / tileSize;
	int worldHeight = arena.height / tileSize;

	rVA.setPrimitiveType(sf::Quads);
	rVA.resize(worldWidth * worldHeight * verticeNumber);

	int currentVertex = 0;
	srand((int)time(0));
	for(int w=0 ; w<worldWidth ; ++w)
	{
		for(int h=0 ; h<worldHeight ; ++h)
		{
			rVA[currentVertex + 0].position = sf::Vector2f(w*tileSize , h*tileSize);
			rVA[currentVertex + 1].position = sf::Vector2f((w+1)*tileSize , h*tileSize);
			rVA[currentVertex + 2].position = sf::Vector2f((w+1)*tileSize , (h+1)*tileSize);
			rVA[currentVertex + 3].position = sf::Vector2f(w*tileSize , (h+1)*tileSize);

			if(h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				rVA[currentVertex + 0].texCoords = sf::Vector2f(0 , 0 + tileTypes*tileSize);
				rVA[currentVertex + 1].texCoords = sf::Vector2f(tileSize , 0 + tileTypes*tileSize);
				rVA[currentVertex + 2].texCoords = sf::Vector2f(tileSize , tileSize + tileSize*tileTypes);
				rVA[currentVertex + 3].texCoords = sf::Vector2f(0 , 0 + tileSize*tileTypes);
			}
			else
			{
				int random = (rand()%tileTypes);	
				int verticalOffset = tileSize * random;

				rVA[currentVertex + 0].texCoords = sf::Vector2f(0 , verticalOffset);
				rVA[currentVertex + 1].texCoords = sf::Vector2f(tileSize , 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = sf::Vector2f(tileSize , tileSize + verticalOffset);
				rVA[currentVertex + 3].texCoords = sf::Vector2f(0 , tileSize + verticalOffset);
			}

			currentVertex += verticeNumber;
		}
	}


	return tileSize;
}

