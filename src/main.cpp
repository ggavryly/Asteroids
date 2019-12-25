#include "main.hpp"
#include "Game.hpp"
#include "InitOptions.hpp"

int main(int argc, char **argv)
{
	Game game;
	if (argc > 1)
	{
		InitOptions *init = new InitOptions(std::string(argv[1]));
		game.init_ = init;
	}
	else
		run(new Game);
	return 0;
}