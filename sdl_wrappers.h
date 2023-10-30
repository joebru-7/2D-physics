#pragma once

#include "sdl.h"
#include<utility>
#include "Point.h"

struct SDL_context
{
	int errorcode;
	
	SDL_context() noexcept : errorcode(SDL_Init(SDL_INIT_EVERYTHING))
	{}
	
	SDL_context(const SDL_context&) = delete;
	SDL_context& operator=(const SDL_context&) = delete;

	SDL_context(SDL_context&& other) noexcept
	{
		errorcode = std::exchange(other.errorcode, -1);
	}
	SDL_context& operator=(SDL_context&& other) noexcept
	{
		errorcode = std::exchange(other.errorcode, -1);
		return *this;
	}

	~SDL_context() noexcept
	{
		if(errorcode == 0)
			SDL_Quit();
	}

	explicit operator bool()
	{
		return errorcode == 0;
	}

	const char* GetError()
	{
		return SDL_GetError();
	}
};


struct Window
{
	SDL_Window* _window;

	Window(
		const char* title = "my title",int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED,
		int w = 1280,int h = 720, Uint32 flags = 0) noexcept
		:_window(SDL_CreateWindow(title,x, y, w,h,flags))
		{}

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&& other) noexcept
	{
		_window = std::exchange(other._window,nullptr);
	}
	Window& operator=(Window&& other) noexcept
	{
		_window = std::exchange(other._window, nullptr);
		return *this;
	}

	auto getWidthandHeight()
	{
		int widht, height;
		SDL_GetWindowSize(_window, &widht, &height);
		return Point{ widht,height };
	}

	~Window()
	{
		SDL_DestroyWindow(_window);
	}

	operator SDL_Window*()
	{
		return _window;
	}
};

constexpr uint32_t computePackedColorValue(Uint8 r, Uint8 g, Uint8 b)
{
	return r << 16 | g << 8 | b << 0;
}

enum class Color : uint32_t
{
	black = 0,
	white = computePackedColorValue(255, 255, 255),
	red = 255 << 16,
	green = 255 << 8,
	blue = 255 << 0,
	purple = computePackedColorValue(255, 0, 255),

};


struct Renderer
{
	SDL_Renderer* _renderer;
	Renderer(Window& window, int index = -1,Uint32 flags = 0)
		:_renderer(SDL_CreateRenderer(window,index,flags))
	{}


	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	Renderer(Renderer&& other) noexcept
	{
		_renderer = std::exchange(other._renderer, nullptr);
	}
	Renderer& operator=(Renderer&& other) noexcept
	{
		_renderer = std::exchange(other._renderer, nullptr);
		return *this;
	}
	~Renderer()noexcept
	{
		SDL_DestroyRenderer(_renderer);
	}

	operator SDL_Renderer*() noexcept
	{
		return _renderer;
	}

	void Preset()
	{
		SDL_RenderPresent(_renderer);
	}

	int SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
	{
		return SDL_SetRenderDrawColor(_renderer, r, g, b, a);
	}

	int SetDrawColor(Color color, Uint8 a = 255)
	{

		Uint8 r = (((uint32_t)color) >> 16) & (uint32_t)255;
		Uint8 g = (((uint32_t)color) >> 8) & (uint32_t)255;
		Uint8 b = (((uint32_t)color) >> 0) & (uint32_t)255;
		return SDL_SetRenderDrawColor(_renderer, r, g, b, a);
	}

	Color getDrawColor()
	{
		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(_renderer, &r, &g, &b, &a);

		return (Color)computePackedColorValue(r, g, b);
	}
		

	int Clear()
	{
		return SDL_RenderClear(_renderer);
	}

	int DrawPoint(int x,int y)
	{
		return SDL_RenderDrawPoint(_renderer,x, y);
	}

	int DrawPoint(Point p)
	{
		return SDL_RenderDrawPoint(_renderer, p.x, p.y);
	}

	int DrawPoint(float x, float y)
	{
		return SDL_RenderDrawPointF(_renderer, x, y);
	}

	int DrawPoint(FPoint p)
	{
		return SDL_RenderDrawPointF(_renderer, p.x, p.y);
	}

	int DrawLines(const FPoint* points, int count)
	{
		return SDL_RenderDrawLinesF(_renderer, points, count);
	}	
	int DrawLines(const Point* points, int count)
	{
		return SDL_RenderDrawLines(_renderer, points, count);
	}

	template <typename T>
	int Draw(T& obj)
	{
		return obj.Draw(*this);
	}

};
