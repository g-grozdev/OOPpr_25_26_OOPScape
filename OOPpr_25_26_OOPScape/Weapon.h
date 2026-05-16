#pragma once
#include "Position.h"

class Weapon
{
	int damage;
	int range;
	int AOE;
	bool pierce;
	Position start;
	int direction;

	void copy_from_partial(const Weapon& wp);

public:
	Weapon(int dmg, int rng, int aoe, bool _pierce);
	Weapon(const Weapon& wp, const Position& _start, int _direction);
	
	int get_damage() const;
	void set_damage(int dmg);
	int get_range() const;
	void set_range(int rng);
	int get_AOE() const;
	void set_AOE(int aoe);
	bool get_pierce() const;
	void set_pierce(bool _pierce);
	const Position& get_start() const;
	void set_start(const Position& _start);
	int get_direction() const;
	void set_direction(int _direction);
};

