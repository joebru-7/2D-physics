#include <iostream>
#include <vector>
#include <execution>

#include "sdl_wrappers.h"
#include "player.h"
#include "Asteroid.h"
#include "line.h"
#include "Bullet.h"
#include "AsteroidSpawner.h"
#include "Rectangle.h"

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);
	std::cout << std::boolalpha;

	SDL_context con{};
	if (!con)
	{
		std::cout << "SDL initialization failed. SDL Error: " << con.GetError();
		return -1;
	}

	std::cout << "SDL initialization succeeded!\n";

	Window window{};

	auto [width, height] = window.getWidthandHeight();

	FRectangle windowBounds{};
	{
		Rectangle intBounds{};
		SDL_GetDisplayBounds(0, &intBounds);
		windowBounds = (FRectangle) intBounds;
	}
	Renderer renderer{ window };

	Player player;
	player.rotationAngle += 2;

	Uint64 now = SDL_GetPerformanceCounter(), last = SDL_GetPerformanceCounter();
	float ticsPerSec = (float)SDL_GetPerformanceFrequency();

	std::vector<Asteroid> asteroids{};

	AsteroidSpawner spawner = {height,width};

	for (size_t i = 0; i < 1000; i++)
	{
		asteroids.push_back(spawner.Create());
	}

	std::vector<Bullet> bullets{};
	for (size_t i = 0; i < 1000; i++)
	{
		bullets.emplace_back(player);
	}

	while (true)
	{
		last = std::exchange(now, SDL_GetPerformanceCounter());
		float deltatime = (now - last) / ticsPerSec;

		std::cout <<
			deltatime * 1000 << "\tms\t" <<
			1 / deltatime << "\tfps\t " <<
			asteroids.size() << " asteroids\t" <<
			bullets.size() << " bullets\t" <<
			'\n';// << std::flush;

	//keybord
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
				case SDL_Scancode::SDL_SCANCODE_RETURN:
					bullets.emplace_back(player);
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

		player.Update(deltatime);
		bool playerIntersectsAsteroid = false;

	//bullets
		renderer.SetDrawColor(Color::white);
		{
			auto last = bullets.end();
			for (int i = (int)bullets.size() - 1; i >= 0; --i)
			{
				bullets[i].Update(deltatime);
				auto bound = bullets[i].calculateBounds();
				if (!(bound.isIntersecting(windowBounds)))
				{
					std::swap(bullets[i], *(--last));
				}
				bullets[i].Draw(renderer);

			}
			bullets.erase(last, bullets.end());
		}

	//asteroids
		asteroids.push_back(spawner.Create());
		renderer.SetDrawColor(Color::blue);
		{
			auto last = asteroids.size();
			for (int i = (int)asteroids.size() - 1; i >= 0; --i)
			{
				auto& asteroid = asteroids[i];
				asteroid.Update(deltatime);

				//inside window?
				auto bound = asteroid.calculateBounds();
				if (!bound.isIntersecting(windowBounds))
				{
					std::swap(asteroid, asteroids[--last]);
					continue;
				}

				//shot at?
				for (auto& bullet : bullets)
				{
					if (asteroid.collidesWith(bullet))
					{
						if (asteroid.scale < 0.5f)
						{
							std::swap(asteroid, asteroids[--last]);
						}
						else
						{
							auto nAsteroid = asteroid.Split();
							nAsteroid.Update(deltatime);
							nAsteroid.Draw(renderer);
							asteroids.push_back(nAsteroid);
							if(last != asteroids.size() - 1)
							{
								std::swap(nAsteroid, asteroids[last++]);
							}
							else
							{
								asteroids.push_back(nAsteroid);
								last++;
							}
						}
						goto nextAsteroid;
					}
				}

				asteroid.Draw(renderer);
				playerIntersectsAsteroid |= player.collidesWith(asteroid);
			nextAsteroid:
				;
			}
			auto it = asteroids.begin();
			std::advance(it, last);
			asteroids.erase(it, asteroids.end());
		}
	
	//player
		renderer.SetDrawColor(playerIntersectsAsteroid ? Color::red : Color::green);
		renderer.Draw(player);


		renderer.Preset();
	}

quitGame:

	return 0;
}

//*/
