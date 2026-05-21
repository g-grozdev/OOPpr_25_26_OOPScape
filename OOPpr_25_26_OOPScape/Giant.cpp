#include "Giant.h"

Giant::Giant(int x, int y, const int& m_c) : Enemy(250, 250, x, y, 50, 2, 0, true, nullptr, nullptr, m_c) { }

bool Giant::move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero, int direction)
{
	if (move_counter % 3 != 2) 
	{
		Enemy::move(tiles, tar, hero, direction);
	}

	return true;
}

Weapon Giant::attack(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int direction)
{
	if (move_counter % 3 != 2)
	{
		int dir = target_is_in_range(tiles, Position(x, y), tar, hero);
		if (dir != -1) 
		{
			return Character::attack(tiles, tar, hero, dir);
		}
	}
	return Weapon(0, -1, 0, false);
}
