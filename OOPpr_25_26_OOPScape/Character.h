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

	virtual Weapon attack(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int direction);

	const Weapon& get_weapon() const;
	void set_weapon(const Weapon& _wp);
};

