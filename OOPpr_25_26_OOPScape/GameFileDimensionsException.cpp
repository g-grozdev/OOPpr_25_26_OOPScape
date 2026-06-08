#include "GameFileDimensionsException.h"

GameFileDimensionsException::GameFileDimensionsException(const std::string& msg, int _size) : GameFileException(msg), size(_size), 
	MIN(2), MAX(64) { }

int GameFileDimensionsException::get_size() const
{
	return size;
}

int GameFileDimensionsException::get_MIN() const
{
	return MIN;
}

int GameFileDimensionsException::get_MAX() const
{
	return MAX;
}
