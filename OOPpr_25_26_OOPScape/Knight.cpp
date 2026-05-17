#include "Knight.h"
#include <iostream>

Knight::Knight(int x, int y) : Hero(150, 150, x, y, 35, 2, 0, true, 5), shield_hp(0), MAX_SHIELD_HP(50) { }

void Knight::take_damage(int dmg)
{
	if (shield_hp >= dmg) 
	{
		shield_hp -= dmg;
	}
	else 
	{
		dmg -= shield_hp;
		Damageable::take_damage(dmg);
	}
}

bool Knight::ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero, int current_move, int x, int y)
{
	if (last_used_ability != -1 && current_move - last_used_ability <= ability_cooldown) return false;

	shield_hp = MAX_SHIELD_HP;
	last_used_ability = current_move;
	
	return true;
}
