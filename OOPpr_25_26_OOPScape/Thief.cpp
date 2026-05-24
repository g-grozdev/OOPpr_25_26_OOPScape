#include "Thief.h"

Thief::Thief(int x, int y, const int& m_c) : Enemy(60, 60, x, y, 15, 3, 0, false, m_c, 't', nullptr, nullptr) {}

bool Thief::move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero)
{
	Enemy::move(tiles, tar, hero);
	if (move_counter % 2 == 1) 
	{
		Enemy::move(tiles, tar, hero);
	}

	return true;
}

void Thief::print()
{
	std::cout << "thief hp: ";
	Enemy::print();
	if (move_counter % 2 == 1) 
	{
		std::cout << "thief moves twice\n";
	}
	else 
	{
		std::cout << "thief moves twice next move\n";
	}
}
