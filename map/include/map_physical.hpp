#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <cassert>

namespace td {
namespace map {

struct block
{
	private:
		bool m_walkable = false;
		bool m_buildable = false;
		bool m_special = false;

	public:
		void setWalkable(bool _state) { m_walkable = _state; }
		void setBuildable(bool _state) { m_buildable = _state; }
		void setSpecial(bool _state) { m_special = _state; }
		bool isWalkable() { return m_walkable; }
		bool isBuildable() { return m_buildable; }
		bool isSpecial() { return m_special; }
};

struct physical
{
	private:
		std::vector<block> m_data;
		SDL_Point m_blSize;
		int m_blockSize;

	public:
		physical() {}

		void init(SDL_Point _blocks, int _bSize)
		{
			assert(_blocks.x >= 0 && _blocks.y >= 0);
			assert(_bSize >= 0);
			m_blSize = _blocks;
			m_data.resize(m_blSize.y * m_blSize.x);
			m_blockSize = _bSize;
		}

		block& content (SDL_Point _pos)
		{
			assert(_pos.x < m_blSize.x && _pos.y < m_blSize.y);
			return m_data[_pos.y*m_blSize.x + _pos.x];
		}

		const block& content (SDL_Point _pos) const
		{
			assert(_pos.x < m_blSize.x && _pos.y < m_blSize.y);
			return m_data[_pos.y*m_blSize.x + _pos.x];
		}

		SDL_Point blocks() const
		{
			return m_blSize;
		}

		SDL_Point blockPos(SDL_Point _block) const
		{
			SDL_Point poi;
			poi.x = m_blockSize*_block.x + m_blockSize/2;
			poi.y = m_blockSize*_block.y + m_blockSize/2;
			return poi;
		}

		void render(SDL_Renderer* _renderer, SDL_Rect _camera)
		{
			SDL_Rect fillRect;
			fillRect.w = _camera.w/m_blSize.x;
			fillRect.h = _camera.h/m_blSize.y;

			for(SDL_Point iter = {0, 0}; iter.y < m_blSize.y; iter.y++)
			{
				for (iter.x = 0; iter.x < m_blSize.x; iter.x++)
				{
					auto& b = content(iter);
					fillRect.x = fillRect.w*iter.x;
					fillRect.y = fillRect.h*iter.y;

					if(b.isSpecial())
					{
						SDL_SetRenderDrawColor(_renderer, 0x7F, 0xFF, 0x10, 0xFF );
					} else if(b.isWalkable()) {
						SDL_SetRenderDrawColor(_renderer, 0x1F, 0x1F, 0x7F, 0xFF );
					} else if(b.isBuildable()) {
						SDL_SetRenderDrawColor(_renderer, 0x1F, 0x7F, 0x1F, 0xFF );
					} else {
						SDL_SetRenderDrawColor(_renderer, 0x1F, 0x1F, 0x1F, 0xFF );
					}
					SDL_RenderFillRect(_renderer, &fillRect);
				}
			}

			SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0x00, 0xFF);
			for(SDL_Point iter = {0, 0}; iter.y < m_blSize.y; iter.y++)
			{
				SDL_RenderDrawLine(_renderer, 0, fillRect.h*iter.y, _camera.w, fillRect.h*iter.y);
			}
			for (SDL_Point iter = {0, 0}; iter.x < m_blSize.x; iter.x++)
			{
				SDL_RenderDrawLine(_renderer, fillRect.w*iter.x, 0, fillRect.w*iter.x, _camera.h );
			}
		}
};

}
}
