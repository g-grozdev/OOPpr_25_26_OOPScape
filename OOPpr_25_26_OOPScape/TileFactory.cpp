#include "TileFactory.h"

Tile TileFactory::create_tile(char tile_type, int x, int y)
{
	Tile result(-1, -1, Effect::NONE, false, false);

	switch (tile_type) 
	{
	case ' ':
		result = Tile(x, y, Effect::NONE, true, false);
		break;
	case '*':
		result = Tile(x, y, Effect::NONE, false, false);
		break;
	case '+':
		result = Tile(x, y, Effect::HEAL, true, false);
		break;
	case '@':
		result = Tile(x, y, Effect::POISON, true, false);
		break;
	case '#':
		result = Tile(x, y, Effect::HIDE, true, false);
		break;
	case 'F':
		result = Tile(x, y, Effect::NONE, true, true);
		break;
	}

	return result;
}
