#include "Weapon.h"

void Weapon::copy_from_partial(const Weapon& wp)
{
	damage = wp.damage;
	range = wp.range;
	AOE = wp.AOE;
	pierce = wp.pierce;
}

Weapon::Weapon(int dmg, int rng, int aoe, bool _pierce) : damage(dmg), range(rng), AOE(aoe), pierce(_pierce), start(-1, -1),
direction(-1) { }

Weapon::Weapon(const Weapon& wp, const Position& _start, int _direction)
{
	copy_from_partial(wp);
	start = _start;
	direction = direction;
}

int Weapon::get_damage() const
{
	return damage;
}

void Weapon::set_damage(int dmg)
{
	if (dmg < 0) return;
	damage = dmg;
}

int Weapon::get_range() const
{
	return range;
}

void Weapon::set_range(int rng)
{
	if (rng < 0) return;
	range = rng;
}

int Weapon::get_AOE() const
{
	return AOE;
}

void Weapon::set_AOE(int aoe)
{
	if (aoe < 0) return;
	AOE = aoe;
}

bool Weapon::get_pierce() const
{
	return pierce;
}

void Weapon::set_pierce(bool _pierce)
{
	pierce = _pierce;
}

const Position& Weapon::get_start() const
{
	return start;
}

void Weapon::set_start(const Position& _start)
{
	start = _start;
}

int Weapon::get_direction() const
{
	return direction;
}

void Weapon::set_direction(int _direction)
{
	if (direction < 0 || direction > 3) return;
	direction = _direction;
}
