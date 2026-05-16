#include "Tile.h"

Tile::Tile(int x, int y, Effect _eff, bool _walk) : pos(x, y), eff(_eff), walkable(_walk) { }

const Position& Tile::get_pos() const
{
	return pos;
}

void Tile::set_pos(const Position& _pos)
{
	pos = _pos;
}

const Effect& Tile::get_effect() const
{
	return eff;
}

void Tile::set_effect(const Effect& _eff)
{
	eff = _eff;
}

bool Tile::get_walkability() const
{
	return walkable;
}

void Tile::set_walkability(bool _walk)
{
	walkable = _walk;
}
