#include <iostream>
#include <vector>
#include <random>
#include <execution>

#include "sdl_wrappers.h"
#include "player.h"
#include "Asteroid.h"
#include "line.h"

//Renderer* debug_renderer;
std::vector<FPoint> debug_points{};

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	SDL_context con{};
	if (!con)
	{
		std::cout << "SDL initialization failed. SDL Error: " << con.GetError();
		return -1;
	}

	std::cout << "SDL initialization succeeded!\n";

	Window window{};

	auto [width, height] = window.getWidthandHeight();

	Renderer renderer{ window };

	Player player;

	Uint64 now = SDL_GetPerformanceCounter(), last = SDL_GetPerformanceCounter();
	float ticsPerSec = (float)SDL_GetPerformanceFrequency();

	std::vector<Asteroid> asteroids{};

	std::random_device rd;
	std::default_random_engine en(rd());

	std::uniform_int_distribution  heightDistribution{ 0,height };
	std::uniform_int_distribution  widhtDistribution{ 0,width };
	std::uniform_real_distribution angleDistribution{ 0.0,6.28 };
	std::uniform_real_distribution speedDistribution{ 1.f,20.f };

	for (size_t i = 0; i < 1; i++)
	{
		//TODO Make factory
		asteroids.push_back(Asteroid(
			FPoint{ (float)widhtDistribution(en),(float)heightDistribution(en) },
			{ 0,0 },//FromAngle(angleDistribution(en), speedDistribution(en)),
			(float)angleDistribution(en),
			0//speedDistribution(en) * (heightDistribution(en) % 2 == 0 ? 1 : -1)
		));
	}

	Line la{};
	la.worldpoints[0] = { 200,200 };
	la.worldpoints[1] = { 200,300 };
	Line lb{};
	lb.worldpoints[0] = { 450,200 };
	lb.worldpoints[1] = { 400,300 };
	


	while (true)
	{
		last = std::exchange(now, SDL_GetPerformanceCounter());

		float deltatime = (now - last) / ticsPerSec;
		std::cout <<
			deltatime * 1000 << "\tms\t" <<
			1 / deltatime << "\tfps\t " <<
			asteroids.size() << " asteroids" <<
			'\n';// << std::flush;

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
				case SDL_Scancode::SDL_SCANCODE_SPACE:
					player.setBreaking(my_event.key.type == SDL_KEYDOWN);
					break;

				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				lb.worldpoints[my_event.button.button == 1 ? 0:1] = { (float)my_event.button.x,(float)my_event.button.y };
				break;
			default:
				break;
			}
		}

		renderer.SetDrawColor(Color::black);
		renderer.Clear();

		player.Update(deltatime);
		bool playerIntersectsAsteroid = false;

		renderer.SetDrawColor(Color::blue);
		for (auto& asteroid : asteroids)
		{
			asteroid.Update(deltatime);
			asteroid.Draw(renderer);
			playerIntersectsAsteroid |= player.collidesWith(asteroid);
		}

		renderer.SetDrawColor(playerIntersectsAsteroid ? Color::red : Color::green);
		renderer.Draw(player);

		renderer.SetDrawColor(lb.collidesWith(asteroids[0]) ? Color::red : Color::green);

		//renderer.Draw(la);
		renderer.Draw(lb);

		renderer.SetDrawColor(Color::purple);
		for (auto& point : debug_points)
		{
			renderer.DrawPoint(point);
		}
		debug_points.clear();

		renderer.Preset();
	}

quitGame:

	return 0;
}

//*/
