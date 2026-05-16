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
			if (tiles[i][j].get_walkability() && target_is_in_range(tiles, Position(i, j), tar, hero))
			{
				(*visited.get()).push(convert_coordinates(i, j, n));
				(*prev.get())[i][j] = 4;
			}
		}
	}
}


Enemy::Enemy(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, 
	const std::shared_ptr<std::vector<std::vector<int>>>& _prev, const std::shared_ptr<std::queue<int>>& _visited) : 
	Character(_hp, _mhp, _x, _y, dmg, rng, aoe, _pierce), prev(_prev), visited(_visited) { }



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
