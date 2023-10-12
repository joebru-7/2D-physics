#pragma once
#include "sdl.h"
#include<utility>
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
	return r << 3 | g << 2 | b << 1;
}

enum class Color : uint32_t
{
	black = 0,
	white = computePackedColorValue(255, 255, 255),
	red = 255 << 3,
	green = 255 << 2,
	blue = 255 << 1

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

		Uint8 r = ((int)color >> 3) & 255;
		Uint8 g = ((int)color >> 2) & 255;
		Uint8 b = ((int)color >> 1) & 255;
		return SDL_SetRenderDrawColor(_renderer, r, g, b, a);
	}

	int Clear()
	{
		return SDL_RenderClear(_renderer);
	}

	int Drawpoint(int x,int y)
	{
		return SDL_RenderDrawPoint(_renderer,x, y);
	}

	template <typename T>
	int Draw(T&)
	{
		T.Draw(*this);
	}

};
