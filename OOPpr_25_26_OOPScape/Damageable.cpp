#include "Damageable.h"

Damageable::Damageable(int _hp, int _mhp) : hp(_hp), MAX_HP(_mhp) { }

void Damageable::take_damage(int dmg)
{
	if (dmg > hp) 
	{
		hp = 0;
		return;
	}
	hp -= dmg;
}

void Damageable::heal(int hl)
{
	if (hp + hl > MAX_HP) hp = MAX_HP;
	else hp += hl;
}

int Damageable::get_hp() const
{
	return hp;
}

void Damageable::set_hp(int _hp)
{
	if (_hp < 0 || _hp > MAX_HP) return;
	hp = _hp;
}
