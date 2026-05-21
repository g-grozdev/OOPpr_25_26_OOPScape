#include "Archer.h"

Archer::Archer(int x, int y) : Hero(75, 75, x, y, 25, 5, 0, false, 7) { }

bool Archer::ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int x, int y)
{
	if (last_used_ability != -1 && move_counter - last_used_ability <= ability_cooldown) return false;

	tar = std::make_shared<Target>(x, y, 80, 80);

	return true;
}
