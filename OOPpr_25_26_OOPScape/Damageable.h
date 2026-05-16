#pragma once
class Damageable
{
	int hp;
	const int MAX_HP;

public:
	Damageable(int _hp, int _mhp);
	virtual ~Damageable() = default;

	virtual void take_damage(int dmg) final;
	int get_hp() const;
	void set_hp(int _hp);
};

