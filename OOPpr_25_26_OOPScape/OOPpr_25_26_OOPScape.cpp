#include <iostream>
#include "Labyrinth.h"

int main()
{
	Labyrinth lab("test1.txt");
	if (lab.play() == 1) 
	{
		std::cout << "you escaped successfully!";
	}
	else 
	{
		std::cout << "you have been defeated!";
	}
}
