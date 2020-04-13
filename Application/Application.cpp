#include "pch.h"
#include <SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include "Game.h"

int main(int argc , char *argv[])
{
	Game game;
	bool init = game.Initialize(); 
	if (init) 
	{
		game.RunGame(); 
	}
	game.ShutDown(); 
	return 0;
}