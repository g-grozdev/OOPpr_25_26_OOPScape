#include "Giant.h"

Giant::Giant(int x, int y) : Enemy(250, 250, x, y, 50, 2, 0, true, nullptr, nullptr) { }

bool Giant::move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero, int direction)
{
	if (move_counter % 3 != 2) 
	{
		Enemy::move(tiles, tar, hero, direction);
	}

	return true;
}
