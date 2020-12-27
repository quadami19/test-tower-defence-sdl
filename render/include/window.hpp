#pragma once
#include <stdexcept>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture_storage.hpp"

namespace td {
namespace graphic {

struct window
{
	private:
		std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> m_window;
		std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> m_renderer;

	public:
		window(int _width, int _height) :
			m_window(std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> (createWindow(_width, _height), destroyWindow)),
			m_renderer(std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> (createRenderer(m_window.get()), destroyRenderer))
		{
			SDL_SetRenderDrawColor(m_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
		}

		operator SDL_Window*()
		{
			return m_window.get();
		}

		SDL_Renderer* renderer()
		{
			return m_renderer.get();
		}

		~window()
		{
			m_renderer.release();
			m_window.release();
		}

	private:
		static SDL_Window* createWindow(int _width, int _height)
		{
			SDL_Window* window = SDL_CreateWindow("Tower defence", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);
			if (window == nullptr) throw std::runtime_error("");
			return window;
		}

		static void destroyWindow(SDL_Window* _window)
		{
			SDL_DestroyWindow(_window);
		}

		static SDL_Renderer* createRenderer(SDL_Window* _window)
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr) throw std::runtime_error("");
			return renderer;
		}


		static void destroyRenderer(SDL_Renderer* _renderer)
		{
			SDL_DestroyRenderer(_renderer);
		}
};

}
}
