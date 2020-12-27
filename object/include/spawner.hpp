#pragma once
#include <memory>
#include "object.hpp"

namespace td {

namespace map {
struct object_storage;
}

struct spawner
{
	private:
		std::unique_ptr<object> m_prototype;
		map::object_storage* m_objectsPtr;

	public:
		spawner(std::unique_ptr<object>&& _obj, map::object_storage* _objStor) :
			m_prototype (std::move(_obj)),
			m_objectsPtr (_objStor)
		{}

		void place(SDL_Point _point)
		{
			m_prototype->moveAbs(_point);
		}

		std::pair<size_t, object*> spawn();

};

}
