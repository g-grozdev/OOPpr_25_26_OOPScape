#pragma once
#include "Position.h"
#include "Effect.h"

class Tile
{
	Position pos;
	Effect eff;
	bool walkable;

public:
	Tile(int x, int y, Effect _eff, bool _walk);
};

