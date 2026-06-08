#include "TileFactory.h"

Tile TileFactory::create_tile(char tile_type, int x, int y)
{
	Tile result(-1, -1, Effect::NONE, false, false, ' ');

	switch (tile_type) 
	{
	case ' ':
		result = Tile(x, y, Effect::NONE, true, false, tile_type);
		break;
	case '*':
		result = Tile(x, y, Effect::NONE, false, false, tile_type);
		break;
	case '+':
		result = Tile(x, y, Effect::HEAL, true, false, tile_type);
		break;
	case '@':
		result = Tile(x, y, Effect::POISON, true, false, tile_type);
		break;
	case '#':
		result = Tile(x, y, Effect::HIDE, true, false, tile_type);
		break;
	case 'F':
		result = Tile(x, y, Effect::NONE, true, true, tile_type);
		break;
	default:
		throw GameFileCharacterException("labyrinth has invalid tile type", "tile", tile_type);
		break;
	}

	return result;
}
