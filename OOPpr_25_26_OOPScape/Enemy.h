#pragma once
#include <queue>
#include "Character.h"
#include "Hero.h"

class Enemy : public Character
{
	std::shared_ptr<std::vector<std::vector<int>>> prev;
	std::shared_ptr<std::queue<int>> visited;
	int convert_coordinates(int x, int y, int n);
	int convert_x_coordinate(int c, int n);
	int convert_y_coordinate(int c, int n);
	void reset_prev(int n);
	void fill_visited_initial(int n, const std::vector<std::vector<Tile>>& tiles, const std::shared_ptr<Target>& tar, 
		const std::shared_ptr<Hero>& hero);

public:
	Enemy(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, 
		const std::shared_ptr<std::vector<std::vector<int>>>& _prev, const std::shared_ptr<std::queue<int>>& _visited);
	~Enemy() override = default;

	bool target_is_in_range(const std::vector<std::vector<Tile>>& tiles, const Position& pos, const std::shared_ptr<Target>& tar,
		const std::shared_ptr<Hero>& hero);
	int pathfind(const std::vector<std::vector<Tile>>& tiles, const std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero);
};