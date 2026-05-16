#pragma once
#include <vector>
#include "Tile.h"
#include "Target.h"

class IMoveable 
{
	virtual void move(const std::vector<std::vector<Tile>>& tiles, Target& tar) = 0;
};