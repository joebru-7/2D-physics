#include <iostream>
#include "sdl.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
		return -1;
	}

	std::cout << "SDL initialization succeeded!";
	
	SDL_Window* window = SDL_CreateWindow("my title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	//SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGB888);

	SDL_Point player{ 50,50 };

	while (true)
	{

		SDL_Event my_event;
		while (SDL_PollEvent(&my_event))
		{
			switch (my_event.type)
			{
			case SDL_KEYDOWN:
				std::cout << "pressed " << SDL_GetKeyName(my_event.key.keysym.sym) << '\n';
				switch (my_event.key.keysym.scancode)
				{
				case SDL_Scancode::SDL_SCANCODE_ESCAPE:
					goto quitGame;
					break;
				case SDL_Scancode::SDL_SCANCODE_W:
					player.y -= 10;
					break;
				case SDL_Scancode::SDL_SCANCODE_S:
					player.y += 10; 
					break;
				case SDL_Scancode::SDL_SCANCODE_A:
					player.x -= 10; 
					break;
				case SDL_Scancode::SDL_SCANCODE_D:
					player.x += 10;
					break;

				default:
					break;
				}
				
				break;
			default:
				break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawPoint(renderer, player.x, player.y);
		SDL_RenderPresent(renderer);
	}
quitGame:
	SDL:SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();


	return 0;
}

//*/
