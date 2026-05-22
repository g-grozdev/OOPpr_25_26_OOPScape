#include "Thief.h"

Thief::Thief(int x, int y, const int& m_c) : Enemy(60, 60, x, y, 15, 3, 0, false, m_c, nullptr, nullptr) { }

bool Thief::move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero, int direction)
{
	Enemy::move(tiles, tar, hero, direction);
	if (move_counter % 2 == 1) 
	{
		Enemy::move(tiles, tar, hero, direction);
	}

	return true;
}
