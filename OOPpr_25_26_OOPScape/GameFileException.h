#pragma once
#include <exception>
#include <string>

class GameFileException : public std::exception
{
	std::string message;

public:
	explicit GameFileException(const std::string& msg);

	const char* what() const noexcept override;
};

