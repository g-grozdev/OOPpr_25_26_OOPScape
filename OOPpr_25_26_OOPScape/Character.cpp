#include "Character.h"

Character::Character(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce) : Target(_x, _y, _hp, _mhp),
wp(dmg, rng, aoe, _pierce) { }

Weapon Character::attack(int direction)
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