#include "tower.hpp"
#include "unit.hpp"
#include "spawner.hpp"
#include "shell.hpp"
#include "../../map/include/map_general.hpp"

namespace td {

std::pair<size_t, object*> tower::findTarget(map::general *_map)
{
	auto found = _map->m_objects.findNearest<unit>(m_position);
	m_target = found.first;
	if (m_target == 0) return std::make_pair(0, nullptr);
	else return found;
}

void tower::tick(map::general *_map)
{
	if(m_reloadCounter++ == m_reloadDelay)
	{
		std::pair<size_t, object*> objPtr;

		if (m_target == 0)
		{
			objPtr = findTarget(_map);
			m_target = objPtr.first;
		} else {
			objPtr.second = _map->m_objects.get(m_target);
		}

		if (objPtr.second != nullptr)
		{
			m_shellSpawner->place(m_position);
			auto shellPtr = m_shellSpawner->spawn();
			dynamic_cast<shell*>(shellPtr.second)->setTarget(m_target);
			m_reloadCounter = 0;
		}
		else
		{
			m_target = 0;
			m_reloadCounter = m_reloadDelay;
		}
	}
}

std::unique_ptr<object> tower::clone(size_t _id)
{
	auto obj = std::make_unique<tower>(tower(*this));
	obj->m_id = _id;
	return obj;
}

}
