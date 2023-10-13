#include <iostream>
#include <vector>
#include <random>

#include "sdl_wrappers.h"
#include "player.h"
#include "Asteroid.h"

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

		auto [width, height] = window.getWidthandHeight();

		Renderer renderer{ window };
		//SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGB888);

		Player player;

		Uint64 now = SDL_GetPerformanceCounter(), last = SDL_GetPerformanceCounter();
		float ticsPerSec = SDL_GetPerformanceFrequency();

		std::vector<Asteroid> asteroids{};

		std::random_device rd;
		std::default_random_engine en(rd());

		std::uniform_int_distribution  heightDistribution{ 0,height };
		std::uniform_int_distribution  widhtDistribution { 0,width };
		std::uniform_real_distribution angleDistribution{ 0.0,6.28 };
		std::uniform_real_distribution speedDistribution { 0.0,6.28 };


		while (true)
		{
			last = std::exchange(now, SDL_GetPerformanceCounter());

			float deltatime = (now - last) / ticsPerSec;
			std::cout << deltatime * 1000 << "\tms\t" << 1 / deltatime << "\tfps\t "<< asteroids.size() << " asteroids" << '\n';

			SDL_Event my_event;
			while (SDL_PollEvent(&my_event))
			{
				switch (my_event.type)
				{
				case SDL_KEYUP:
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

			renderer.SetDrawColor(Color::black);
			renderer.Clear();
			asteroids.emplace_back(
				FPoint{ (float)widhtDistribution(en),(float)heightDistribution(en) },
				FromAngle(angleDistribution(en), speedDistribution(en)),
				angleDistribution(en)
				);

			renderer.SetDrawColor(Color::blue);
			for (auto& asteroid : asteroids)
			{
				asteroid.Update(deltatime);
				asteroid.Draw(renderer);
			}

			player.Update(deltatime);


			renderer.SetDrawColor(Color::red);
			renderer.Draw(player);

			renderer.Preset();
		}
	}
quitGame:

	return 0;
}

//*/
