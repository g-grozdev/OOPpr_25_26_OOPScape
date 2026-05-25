#include "Giant.h"

Giant::Giant(int x, int y, const int& m_c) : Enemy(190, 190, x, y, 50, 2, 0, true, m_c, 'g', nullptr, nullptr) {}

bool Giant::move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero)
{
	if (move_counter % 3 != 2) 
	{
		Enemy::move(tiles, tar, hero);
	}

	return true;
}

Weapon Giant::attack(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero)
{
	if (move_counter % 3 != 2)
	{
		return Enemy::attack(tiles, tar, hero);
	}
	return Weapon(0, -1, 0, false);
}

void Giant::print()
{
	std::cout << "giant hp: ";
	Target::print();
	if (move_counter % 3 == 2) 
	{
		std::cout << "giant is asleep\n";
	}
	else 
	{
		std::cout << "giant falls asleep in " << 2 - (move_counter % 3) << " moves\n";
	}
}
