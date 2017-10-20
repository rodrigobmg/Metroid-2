#include "Tile.h"


Tile::Tile()
{
	ID = -1;
}

Tile::Tile(int id, int posX, int posY)
{
	ID = id;
	this->posX = posX;
	this->posY = posY;
}


Tile::~Tile()
{

}
