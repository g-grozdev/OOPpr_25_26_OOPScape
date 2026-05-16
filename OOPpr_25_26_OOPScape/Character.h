#pragma once
#include "Damageable.h"
#include "Position.h"
#include "Weapon.h"
#include "IMoveable.h"

class Character : public Target, public IMoveable
{
protected:
	Weapon wp;

public:
	Character(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce);
	~Character() override = default;

	Weapon attack(int direction);

	const Weapon& get_weapon() const;
	void set_weapon(const Weapon& _wp);
};

