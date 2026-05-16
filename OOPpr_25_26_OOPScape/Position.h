#pragma once

class Position
{
protected:
	int x;
	int y;
	static int MAX;

public:
	Position();
	Position(int _x, int _y);
	virtual ~Position() = default;

	int get_x() const;
	void set_x(int _x);
	int get_y() const;
	void set_y(int _y);

	static int get_max();
	static void set_max(int max);
};

