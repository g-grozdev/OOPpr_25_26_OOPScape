#include "Enemy.h"

int Enemy::convert_coordinates(int x, int y, int n)
{
	return x * n + y;
}

int Enemy::convert_x_coordinate(int c, int n)
{
	return c / n;
}

int Enemy::convert_y_coordinate(int c, int n)
{
	return c % n;
}

void Enemy::reset_prev(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			(*prev.get())[i][j] = -1;
		}
	}
}

void Enemy::fill_visited_initial(int n, const std::vector<std::vector<Tile>>& tiles, const std::shared_ptr<Target>& tar,
	const std::shared_ptr<Hero>& hero)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tiles[i][j].get_walkability() && target_is_in_range(tiles, Position(i, j), tar, hero) != -1)
			{
				(*visited.get()).push(convert_coordinates(i, j, n));
				(*prev.get())[i][j] = 4;
			}
		}
	}
}

int Enemy::pathfind(const std::vector<std::vector<Tile>>& tiles, const std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero)
{
	int n = tiles.size();
	reset_prev(n);

	fill_visited_initial(n, tiles, tar, hero);

	int dir[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

	while (!(*visited.get()).empty())
	{
		for (int i = (*visited.get()).size(); i > 0; i--)
		{
			int ind = (*visited.get()).front();
			int temp_x = convert_x_coordinate(ind, n);
			int temp_y = convert_y_coordinate(ind, n);
			int new_x = -1;
			int new_y = -1;
			for (int j = 0; j < 4; j++)
			{
				new_x = temp_x + dir[j][0];
				new_y = temp_y + dir[j][1];
				if (tiles[new_x][new_y].get_walkability() && (*prev.get())[new_x][new_y] == -1)
				{
					(*visited.get()).push(convert_coordinates(new_x, new_y, n));
					(*prev.get())[new_x][new_y] = j;
				}
			}
			(*visited.get()).pop();
		}
	}

	return (*prev.get())[x][y];
}

bool Enemy::target_is_in_range(const std::vector<std::vector<Tile>>& tiles, const Position& pos, const std::shared_ptr<Target>& tar,
	const std::shared_ptr<Hero>& hero, int direction)
{
	int tar_x = (*tar.get()).get_x();
	int tar_y = (*tar.get()).get_y();
	int hero_x = (*hero.get()).get_x();
	int hero_y = (*hero.get()).get_y();

	int attack_x = pos.get_x();
	int attack_y = pos.get_y();

	int n = tiles.size();
	int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
	bool hit = false;
	for (int i = 0; i <= wp.get_range() && attack_is_in_bounds(attack_x, attack_y, n); i++)
	{
		if (!tiles[attack_x][attack_y].get_walkability())
		{
			attack_x -= dir[direction][0];
			attack_y -= dir[direction][1];
			return check_AOE(tiles, Position(attack_x, attack_y), tar);
		}
		if ((attack_x == tar_x && attack_y == tar_y) || (attack_x == hero_x && attack_y == hero_y))
		{
			if (!wp.get_pierce())
			{
				return check_AOE(tiles, Position(attack_x, attack_y), tar);
			}
			else
			{
				if (check_AOE(tiles, Position(attack_x, attack_y), tar))
				{
					return true;
				}
			}
		}

		attack_x += dir[direction][0];
		attack_y += dir[direction][1];
	}

	return false;
}

bool Enemy::attack_is_in_bounds(int x, int y, int n)
{
	return x > -1 && x < n && y > -1 && y < n;
}

bool Enemy::check_AOE(const std::vector<std::vector<Tile>>& tiles, const Position& pos, const std::shared_ptr<Target>& tar)
{
	int n = tiles.size();
	int AOE = wp.get_AOE();
	reset_prev(n);

	int init_x = pos.get_x();
	int init_y = pos.get_y();

	if (is_within_AOE(init_x, init_y, init_x, init_y, AOE))
	{
		(*visited.get()).push(convert_coordinates(init_x, init_y, n));
		(*prev.get())[init_x][init_y] = 0;
	}

	int dir[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

	while (!(*visited.get()).empty())
	{
		for (int i = (*visited.get()).size(); i > 0; i--)
		{
			int ind = (*visited.get()).front();
			int temp_x = convert_x_coordinate(ind, n);
			int temp_y = convert_y_coordinate(ind, n);
			int new_x = -1;
			int new_y = -1;
			for (int j = 0; j < 4; j++)
			{
				new_x = temp_x + dir[j][0];
				new_y = temp_y + dir[j][1];
				if (tiles[new_x][new_y].get_walkability() && (*prev.get())[new_x][new_y] == -1
					&& is_within_AOE(new_x, new_y, init_x, init_y, AOE))
				{
					(*visited.get()).push(convert_coordinates(new_x, new_y, n));
					(*prev.get())[new_x][new_y] = 0;
				}
			}
			(*visited.get()).pop();
		}
	}

	return (*prev.get())[(*tar.get()).get_x()][(*tar.get()).get_y()] == 0;
}

bool Enemy::is_within_AOE(int x1, int y1, int x2, int y2, int AOE)
{
	int dx = x1 - x2;
	int dy = y1 - y2;
	return dx * dx + dy * dy <= AOE;
}

int Enemy::target_is_in_range(const std::vector<std::vector<Tile>>& tiles, const Position& pos, const std::shared_ptr<Target>& tar,
	const std::shared_ptr<Hero>& hero)
{
	for (int i = 0; i < 4; i++)
	{
		if (target_is_in_range(tiles, pos, tar, hero, i)) return i;
	}
	return -1;
}

Enemy::Enemy(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, const int& m_c,
	const std::shared_ptr<std::vector<std::vector<int>>>& _prev, const std::shared_ptr<std::queue<int>>& _visited) : 
	Character(_hp, _mhp, _x, _y, dmg, rng, aoe, _pierce, m_c), prev(_prev), visited(_visited) { }

bool Enemy::move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero, int direction = -1)
{
	direction = pathfind(tiles, tar, hero);
	switch (direction)
	{
	case 0:
		set_x(get_x() - 1);
		break;
	case 1:
		set_y(get_y() + 1);
		break;
	case 2:
		set_x(get_x() + 1);
		break;
	case 3:
		set_y(get_y() - 1);
		break;
	default:
		break;
	}

	return true;
}