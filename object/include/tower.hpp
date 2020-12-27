#pragma once
#include "object.hpp"

namespace td {

struct spawner;

class tower : public object
{
		size_t m_target;
		int m_reloadDelay = 60;
		int m_reloadCounter = 0;
		spawner* m_shellSpawner;

		std::pair<size_t, object *> findTarget(map::general *_map);
	public:

		tower(SDL_Texture* _tex, SDL_Point _pos, SDL_Point _size, size_t _id, spawner* _spawner) :
			object(_tex, _pos, _size, _id),
			m_shellSpawner(_spawner)
		{}

		tower(const tower& _obj) :
			object(_obj),
			m_target(_obj.m_target),
			m_reloadDelay(_obj.m_reloadDelay),
			m_reloadCounter(0),
			m_shellSpawner(_obj.m_shellSpawner)
		{}

		virtual ~tower() {}

		virtual void tick(map::general *_map) override;

		virtual std::unique_ptr<object> clone(size_t _id) override;
};

}
