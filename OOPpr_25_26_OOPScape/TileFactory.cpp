#include "TileFactory.h"

Tile TileFactory::create_tile(char tile_type, int x, int y)
{
	Tile result(-1, -1, Effect::NONE, false);

	switch (tile_type) 
	{
	case ' ':
		result = Tile(x, y, Effect::NONE, true);
		break;
	case '*':
		result = Tile(x, y, Effect::NONE, false);
		break;
	case '+':
		result = Tile(x, y, Effect::HEAL, true);
		break;
	case '@':
		result = Tile(x, y, Effect::POISON, true);
		break;
	case '#':
		result = Tile(x, y, Effect::HIDE, true);
		break;
	case 'F':
		result = Tile(x, y, Effect::NONE, true);
		break;
	}

	return result;
}
