#pragma once
#include "Weapon.h"
#include "IMoveable.h"
#include "Target.h"

class Character : public Target, public IMoveable
{
protected:
	const int& move_counter;
	Weapon wp;

public:
	Character(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, const int& m_c);
	~Character() override = default;

	Weapon attack(int direction);

	const Weapon& get_weapon() const;
	void set_weapon(const Weapon& _wp);
};

