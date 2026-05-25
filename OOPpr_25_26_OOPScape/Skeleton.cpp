#include "Skeleton.h"

std::shared_ptr<int> Skeleton::communal_bonus_count = nullptr;

void Skeleton::apply_bonus()
{
	int bonus = (*bonus_count.get());
	bonus = (bonus > 4 ? 4 : bonus);
	wp.set_damage(10 + bonus * 5);

	heal(15 * ((*bonus_count.get()) - last_bonus_applied));

	last_bonus_applied = (*bonus_count.get());
}

int Skeleton::get_damage()
{
	if (last_bonus_applied != (*bonus_count.get())) 
	{
		apply_bonus();
	}
	return wp.get_damage();
}

void Skeleton::reset_bonus_count()
{
	communal_bonus_count = nullptr;
}

Skeleton::Skeleton(int x, int y, const int& m_c) :
	Enemy(50, 120, x, y, 10, 1, 0, false, m_c, 's', nullptr, nullptr), bonus_count(nullptr), last_bonus_applied(0) 
{
	if (communal_bonus_count == nullptr) 
	{
		communal_bonus_count = std::make_shared<int>();
	}
	bonus_count = communal_bonus_count;
}

void Skeleton::take_damage(int dmg)
{
	if (hp == 0) return;

	if (last_bonus_applied != (*bonus_count.get())) 
	{
		apply_bonus();
	}

	if (dmg > hp) 
	{
		(*bonus_count.get())++;
	}

	Damageable::take_damage(dmg);
}

Weapon Skeleton::attack(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero)
{
	if (last_bonus_applied != (*bonus_count.get()))
	{
		apply_bonus();
	}

	return Enemy::attack(tiles, tar, hero);
}

const std::shared_ptr<int>& Skeleton::get_bonus_count() const
{
	return bonus_count;
}

void Skeleton::set_bonus_count(const std::shared_ptr<int>& _bonus_count)
{
	bonus_count = _bonus_count;
}

void Skeleton::print()
{
	int damage = get_damage();
	std::cout << "skeleton hp: ";
	Enemy::print();
	std::cout << "current damage: " << damage << '\n';
}
