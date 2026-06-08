#include "GameFileLayoutException.h"

GameFileLayoutException::GameFileLayoutException(const std::string& msg, int _rows, int _cols) : GameFileException(msg), 
	rows(_rows), cols(_cols) { }

int GameFileLayoutException::get_rows() const
{
	return rows;
}

int GameFileLayoutException::get_cols() const
{
	return cols;
}
