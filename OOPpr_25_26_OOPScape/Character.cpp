#include "Character.h"

Character::Character(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, const int& m_c) : Target(_x, _y, _hp, _mhp),
wp(dmg, rng, aoe, _pierce), move_counter(m_c) { }

Weapon Character::attack(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int direction = -1)
{
	return Weapon(wp, Position(x, y), direction);
}

const Weapon& Character::get_weapon() const
{
	return wp;
}

void Character::set_weapon(const Weapon& _wp)
{
	wp = _wp;
}