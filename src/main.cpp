#include "Game.hpp"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		InitOptions *init = new InitOptions(std::string(argv[1]));
	}
	else
		run(new Game);
	return 0;
}