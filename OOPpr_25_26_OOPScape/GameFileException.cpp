#include "GameFileException.h"

GameFileException::GameFileException(const std::string& msg) : message(msg) { }

const char* GameFileException::what() const noexcept
{
	return message.c_str();
}
