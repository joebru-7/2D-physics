#include <iostream>
#include "sdl.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
		return -1;
	}
	else
	{
		std::cout << "SDL initialization succeeded!";
	}
	return 0;
}

//*/
