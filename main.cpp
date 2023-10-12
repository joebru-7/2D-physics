#include <iostream>

#include "sdl_wrappers.h"

int main(int argc, char* argv[])
{
	if (SDL_context con{}; !con)
	{
		std::cout << "SDL initialization failed. SDL Error: " << con.GetError();
		return -1;
	}
	else
	{
		std::cout << "SDL initialization succeeded!";

		Window window{};

		Renderer renderer{ window };
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
			renderer.SetDrawColor(Color::black);
			renderer.Clear();
			renderer.SetDrawColor(Color::red);
			renderer.Drawpoint(player.x, player.y);

			renderer.Preset();
		}
	}
quitGame:

	return 0;
}

//*/
