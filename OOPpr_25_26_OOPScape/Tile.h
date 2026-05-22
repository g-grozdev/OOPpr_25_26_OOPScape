#pragma once
#include "Position.h"
#include "Effect.h"

class Tile
{
	Position pos;
	Effect eff;
	bool walkable;
	bool is_end;

public:
	Tile(int x, int y, Effect _eff, bool _walk, bool _is_end);

	const Position& get_pos() const;
	void set_pos(const Position& _pos);
	const Effect& get_effect() const;
	void set_effect(const Effect& _eff);
	bool get_walkability() const;
	void set_walkability(bool _walk);
	bool get_is_end() const;
	void set_is_end(bool _is_end);
};

