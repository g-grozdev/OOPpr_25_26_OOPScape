#include "Knight.h"

Knight::Knight(int x, int y, const int& m_c) : Hero(150, 150, x, y, 35, 2, 0, true, 5, m_c, 'K'), shield_hp(0), MAX_SHIELD_HP(50) {}

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

bool Knight::ability(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero)
{
	if (last_used_ability != -1 && move_counter - last_used_ability <= ability_cooldown) return false;

	shield_hp = MAX_SHIELD_HP;

	last_used_ability = move_counter;
	
	return true;
}

void Knight::print()
{
	Hero::print();
	std::cout << "sheild HP: " << shield_hp << '\n';
}
