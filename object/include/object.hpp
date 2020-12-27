#pragma once
#include <SDL2/SDL.h>
#include <memory>

namespace td {

namespace map
{
struct general;
}

class object
{
		SDL_Texture* m_texture;

	protected:
		SDL_Point m_position;
		SDL_Point m_size;
		size_t m_id;
		int m_speed = 3;
		int m_hpTotal = 100;
		int m_hpCurrent = 100;
		float m_angle = 0.f;

	public:
		object(SDL_Texture* _tex, SDL_Point _pos, SDL_Point _size, size_t _id) :
			m_texture(_tex),
			m_position(_pos),
			m_size(_size),
			m_id(_id)
		{}

		virtual ~object() {}

		void render(SDL_Renderer* _renderer, SDL_Rect _camera) const
		{
			SDL_Rect renderQuad ({ _camera.x + m_position.x - m_size.x/2, _camera.y + m_position.y - m_size.y/2, m_size.x, m_size.y });
			SDL_RenderCopyEx(_renderer, m_texture, NULL, &renderQuad, 0.f, &m_position, SDL_FLIP_NONE);
		}

		virtual void tick(map::general* _map) = 0;

		virtual std::unique_ptr<object> clone(size_t _id) = 0;
		/*{
			auto obj = std::make_unique<object>(object(*this));
			return obj;
		}*/

		void move(SDL_Point _relativePos) { m_position.x += _relativePos.x; m_position.y += _relativePos.y; }
		void moveAbs(SDL_Point _absPos) { m_position.x = _absPos.x; m_position.y = _absPos.y; }
		bool moveTo(SDL_Point _destPos)
		{
			int dx_t = _destPos.x - m_position.x;
			int dy_t = _destPos.y - m_position.y;
			m_angle = std::atan2((float)dy_t, (float)dx_t);
			int dx = m_speed * std::cos(m_angle);
			int dy = m_speed * std::sin(m_angle);

			dx = std::abs(dx_t) > std::abs(dx) ? dx : dx_t;
			dy = std::abs(dy_t) > std::abs(dy) ? dy : dy_t;

			move(SDL_Point({ dx, dy }));
			return m_position.x == _destPos.x && m_position.y == _destPos.y;
		}

		void damage(int _dHP) { m_hpCurrent -= _dHP; m_hpCurrent = m_hpCurrent < 0 ? 0 : m_hpCurrent; }
		bool isAlive() { return m_hpCurrent; }
/*

*/
		SDL_Point pos() const { return m_position; }
		SDL_Point size() const { return m_size; }
		size_t ID() const { return m_id; }
};

}
