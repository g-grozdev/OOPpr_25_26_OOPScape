#include "Character.h"

Character::Character(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, int _pierce) : Damageable(_hp, _mhp), 
Position(_x, _y), wp(dmg, rng, aoe, _pierce) { }

Weapon Character::attack(int direction)
{
	return Weapon(wp, Position(x, y), direction);
}
