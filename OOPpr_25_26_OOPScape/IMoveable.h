#pragma once
#include <vector>
#include <memory>
#include "Tile.h"
#include "Target.h"
#include "Hero.h"

class IMoveable 
{
public:
	virtual ~IMoveable() = default;
	virtual bool move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero, int direction = -1) = 0;
};