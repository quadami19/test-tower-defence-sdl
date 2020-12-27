#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace td {
namespace graphic {

struct texture
{
	private:

		std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> m_texture;

		texture(SDL_Renderer* _renderer, SDL_Surface* _surface, std::string&& _path, std::string&& _name) :
			m_texture(std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(createTexture(_renderer, _surface), destroyTexture)),
			w(_surface->w),
			h(_surface->h),
			path(_path),
			name(_name)
		{}

		texture(const texture&) = delete;

	public:

		const int w;
		const int h;
		const std::string path;
		const std::string name;

		texture(texture&& _texture) :
			m_texture(std::move(_texture.m_texture)),
			w(_texture.w),
			h(_texture.h),
			path(std::move(_texture.path)),
			name(std::move(_texture.name))
		{}

		static texture createFromFile(SDL_Renderer* _renderer, std::string&& _path, std::string&& _name)
		{

			SDL_Surface* surface = IMG_Load(_path.data());
			if (surface == nullptr) throw std::runtime_error("");
			SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
			return texture (_renderer, surface, std::move(_path), std::move(_name));
		}

		SDL_Texture* get()
		{
			return m_texture.get();
		}

	private:

		static SDL_Texture* createTexture(SDL_Renderer* _renderer, SDL_Surface* _surface)
		{
			SDL_Texture* temp = SDL_CreateTextureFromSurface(_renderer, _surface);
			if (temp == nullptr) throw std::runtime_error("");
			return temp;
		}

		static void destroyTexture(SDL_Texture* _texture)
		{
			SDL_DestroyTexture(_texture);
		}

};

struct texture_storage
{
	private:
		SDL_Renderer* m_renderer;
		std::unordered_map<const std::string, texture, std::hash<std::string>> m_storage;

	public:

		texture_storage(SDL_Renderer* _renderer) :
			m_renderer(_renderer)
		{}

		bool load(std::string _path, std::string _name)
		{
			if(m_storage.find(_name) != m_storage.end()) return false;
			auto temp = texture::createFromFile(m_renderer, std::move(_path), std::move(_name));
			m_storage.insert(std::make_pair(temp.name, std::move(temp)));
			return true;
		}

		bool erase(std::string _name)
		{
			auto iter = m_storage.find(_name);
			if (iter == m_storage.end()) return false;
			m_storage.erase(iter);
			return true;
		}

		texture& get(std::string _name)
		{
			return m_storage.find(_name)->second;
		}

};

}
}
