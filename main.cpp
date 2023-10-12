#include <iostream>

#include "sdl_wrappers.h"
#include "player.h"


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

		Player player;

		Uint64 now = SDL_GetPerformanceCounter(), last = SDL_GetPerformanceCounter();
		float ticsPerSec = SDL_GetPerformanceFrequency();
		while (true)
		{
			//TODO framerate
			last = now;
			now = SDL_GetPerformanceCounter();

			float deltatime = (now-last)/ ticsPerSec;
			//std::cout << deltatime << '\n';

			SDL_Event my_event;
			while (SDL_PollEvent(&my_event))
			{
				switch (my_event.type)
				{
				case SDL_KEYDOWN:
					//std::cout << "pressed " << SDL_GetKeyName(my_event.key.keysym.sym) << '\n';
					switch (my_event.key.keysym.scancode)
					{
					case SDL_Scancode::SDL_SCANCODE_ESCAPE:
						goto quitGame;
						break;
					case SDL_Scancode::SDL_SCANCODE_W:
						player.setAccelerating(my_event.key.type == SDL_KEYDOWN);
						break;
					case SDL_Scancode::SDL_SCANCODE_S:
						//player.y += 10;
						break;
					case SDL_Scancode::SDL_SCANCODE_A:
						player.rotationAngle -= 0.1f;
						break;
					case SDL_Scancode::SDL_SCANCODE_D:
						player.rotationAngle += 0.1f;
						break;

					default:
						break;
					}

					break;
				default:
					break;
				}
			}

			player.Update(deltatime);

			renderer.SetDrawColor(Color::black);
			renderer.Clear();
			renderer.SetDrawColor(Color::red);
			renderer.Draw(player);


			renderer.Preset();
		}
	}
quitGame:

	return 0;
}

//*/
