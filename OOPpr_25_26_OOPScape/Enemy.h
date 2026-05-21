#pragma once
#include <queue>
#include "Character.h"
#include "Hero.h"
#include "Tile.h"

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
	int pathfind(const std::vector<std::vector<Tile>>& tiles, const std::shared_ptr<Target>& tar, const std::shared_ptr<Hero>& hero);
	bool target_is_in_range(const std::vector<std::vector<Tile>>& tiles, const Position& pos, const std::shared_ptr<Target>& tar,
		const std::shared_ptr<Hero>& hero);
	bool attack_is_in_bounds(int x, int y, int n);
	bool check_AOE(const std::vector<std::vector<Tile>>& tiles, const Position& pos, const std::shared_ptr<Target>& tar);
	bool is_within_AOE(int x1, int y1, int x2, int y2, int AOE);

public:
	Enemy(int _hp, int _mhp, int _x, int _y, int dmg, int rng, int aoe, bool _pierce, const int& m_c, 
		const std::shared_ptr<std::vector<std::vector<int>>>& _prev, const std::shared_ptr<std::queue<int>>& _visited);
	~Enemy() override = default;
	bool target_is_in_range(const std::vector<std::vector<Tile>>& tiles, const Position& pos, const std::shared_ptr<Target>& tar,
		const std::shared_ptr<Hero>& hero, int direction);
	bool move(const std::vector<std::vector<Tile>>& tiles, std::shared_ptr<Target>& tar, const std::shared_ptr<Hero> hero, int direction) override;
};