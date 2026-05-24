#pragma once
#include <vector>
#include <memory>

class Tile;
class Target;
class Hero;

class IMoveable 
{
public:
	virtual ~IMoveable() = default;
	virtual bool move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero) = 0;
};