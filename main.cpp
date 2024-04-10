#include <iostream>
#include <vector>
#include <execution>

#include "sdl_wrappers.h"
#include "line.h"
#include "Rectangle.h"
#include "QuadTree.h"
#include "Box.h"
#include "Hit.h"
#include "Wall.h"

Renderer* debugRenderer;
bool fixedDeltatime = false;


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
	debugRenderer = &renderer;


	std::vector<Box> boxes{};
	Wall bottomWall = Wall(FPoint{20,height-20.f},width-40.f,10.f);

	Uint64 now = SDL_GetPerformanceCounter(), last = SDL_GetPerformanceCounter();
	float ticsPerSec = (float)SDL_GetPerformanceFrequency();

	while (true)
	{
		last = std::exchange(now, SDL_GetPerformanceCounter());
		float deltatime = (now - last) / ticsPerSec;

		//clear screen with black
		renderer.SetDrawColor(Color::black);
		renderer.Clear();

		renderer.SetDrawColor(fixedDeltatime ? Color::blue : Color::red);
		renderer.Draw(FPoint{ 10,10 });
		if (fixedDeltatime)
		{
			deltatime = 0.0001f;
		}
		//std::cout <<
		//	deltatime * 1000 << "\tms\t" <<
		//	1 / deltatime << "\tfps\t " <<
		//	'\n';// << std::flush;

	//keybord
		SDL_Event my_event;
		while (SDL_PollEvent(&my_event))
		{
			switch (my_event.type)
			{
			case SDL_QUIT:
				goto quitGame;
				break;
			case SDL_KEYUP:
			case SDL_KEYDOWN:
				//std::cout << "pressed " << SDL_GetKeyName(my_event.key.keysym.sym) << '\n';
				switch (my_event.key.keysym.scancode)
				{
				case SDL_Scancode::SDL_SCANCODE_ESCAPE:
					goto quitGame;
					break;
				case SDL_Scancode::SDL_SCANCODE_F:
					if (my_event.key.state == SDL_PRESSED)
					{
						fixedDeltatime = !fixedDeltatime;
					}
					break;
				default:
					break;
				}
				break;
			//case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				boxes.push_back({ FPoint{(float)my_event.button.x,(float)my_event.button.y} });
				//boxes.back().rotationAngle
				break;
			default:
				break;
			}
		}

		renderer.SetDrawColor(Color::gray);
		renderer.Draw(bottomWall);

		renderer.SetDrawColor(Color::red);
		for (auto& box : boxes)
		{
			box.Update(deltatime);
			renderer.Draw(box);
		}
		renderer.SetDrawColor(Color::green);
		if(boxes.size() >0)
		for (size_t i = 0; i < boxes.size() - 1; i++)
		{
			auto& box1 = boxes[i];
			Hit hit;
			if (box1.collidesWith(bottomWall, &hit))
			{
				renderer.Draw(hit.location);
				box1.handleCollision(bottomWall, hit);
				//box1.velocity = box1.velocity * ((box1.mass - bottomWall.mass) / (box1.mass + bottomWall.mass));
			}
			for (size_t ii = i + 1; ii < boxes.size(); ii++)
			{
				auto& box2 = boxes[ii];
				Hit hit;
				if (box1.collidesWith(box2,&hit))
				{
					box1.handleCollision(box2, hit);
					renderer.Draw(hit.location);
					// box1.pos;
				}

			}
		}

		renderer.Preset();

	}

quitGame:

	return 0;
}

//*/
