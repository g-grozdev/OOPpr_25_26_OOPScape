#pragma once
#include <vector>
#include <memory>
#include "Tile.h"
#include "Target.h"

class IMoveable 
{
public:
	virtual void move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar) = 0;
	virtual ~IMoveable() = default;
};