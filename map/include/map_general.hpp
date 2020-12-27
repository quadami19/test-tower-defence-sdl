#pragma once
#include "../../object/include/object_storage.hpp"
#include "map_physical.hpp"

namespace td {
namespace map {

struct general
{
	private:

	public:

		physical       m_physical;
		object_storage m_objects;

		general() {}

		void init(SDL_Point _size, int _bSize)
		{
			m_physical.init(_size, _bSize);
		}

		void render(SDL_Renderer *_renderer, SDL_Rect _camera)
		{
			m_physical.render(_renderer, _camera);
			m_objects.render(_renderer, _camera);
		}

		void tick()
		{
			m_objects.tick(this);
		}

};

}
}
