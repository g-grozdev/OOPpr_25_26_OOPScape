#include "Archer.h"

Archer::Archer(int x, int y, const int& m_c) : Hero(75, 75, x, y, 25, 5, 0, false, 7, m_c, 'A') {}

bool Archer::ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero)
{
	if (last_used_ability != -1 && move_counter - last_used_ability <= ability_cooldown) return false;

	tar = std::make_shared<Target>(x, y, 80, 80, '$');

	last_used_ability = move_counter;

	return true;
}
