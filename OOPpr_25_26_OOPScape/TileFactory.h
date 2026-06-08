#pragma once
#include "Tile.h"
#include "GameFileCharacterException.h"

class TileFactory
{
public:
	static Tile create_tile(char tile_type, int x, int y);
};

