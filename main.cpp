#include <iostream>
#include <vector>
#include "sdl_wrappers.h"
#include "Rectangle.h"
#include "Box.h"
#include "Hit.h"
#include "Wall.h"
#include "Magnet.h"

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
	FRectangle windowBounds = (FRectangle) window.getBounds();

	Renderer renderer{ window };

	std::vector<Box> boxes{};
	Wall bottomWall = Wall(FPoint{20,height-20.f},width-40.f,10.f);

	Uint64 now = SDL_GetPerformanceCounter(), last = SDL_GetPerformanceCounter();
	float ticsPerSec = (float)SDL_GetPerformanceFrequency();

	Magnet magnet;
	magnet.pos = { 300,300 };
	magnet.strength = 10000;

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
				if ((int)my_event.button.button == 1) //left
				{
					boxes.push_back({ FPoint{(float)my_event.button.x,(float)my_event.button.y} });
					boxes.back().angularVelocity = .01f;
				}
				else if ((int)my_event.button.button == 3) //right
				{
					magnet.pos = { (float)my_event.button.x, (float)my_event.button.y };
				}
				break;
			default:
				break;
			}
		}

		renderer.SetDrawColor(Color::gray);
		renderer.Draw(bottomWall);

		renderer.SetDrawColor(Color::white);
		renderer.Draw(magnet.pos);

		renderer.SetDrawColor(Color::red);
		std::erase_if(boxes, [&](const Box& box) {return !box.calculateBounds().isIntersecting(windowBounds); });
		for (auto& box : boxes)
		{
			float distance2 = (magnet.pos-box.pos).lengthSqured();
			float magneticforce = (magnet.strength) / (distance2);
			box.applyForce(magneticforce*deltatime,(magnet.pos-box.pos)*(1.f/sqrt(distance2)));
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
			}
			for (size_t ii = i + 1; ii < boxes.size(); ii++)
			{
				auto& box2 = boxes[ii];
				Hit hit;
				if (box1.collidesWith(box2,&hit))
				{
					box1.handleCollision(box2, hit);
					renderer.Draw(hit.location);
				}
			}
		}

		renderer.Preset();
	}//main game loop

quitGame:

	return 0;
}

//*/
