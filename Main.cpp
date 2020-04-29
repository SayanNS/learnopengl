#include "Game.h"

int main(int argv, char** argc)
{
	Game game;

	bool success = game.Initialize();
	
	if (success)
	{
		game.RunLoop();
	}
	else
	{
		game.Shutdown();

		return 1;
	}

	return 0;
}