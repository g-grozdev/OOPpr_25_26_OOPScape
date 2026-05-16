#include "Tile.h"

Tile::Tile(int x, int y, Effect _eff, bool _walk) : pos(x, y), eff(_eff), walkable(_walk) { }
