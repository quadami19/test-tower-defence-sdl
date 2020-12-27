#include "../include/shell.hpp"
#include "../include/unit.hpp"
#include "../../map/include/map_general.hpp"

void td::shell::tick(td::map::general *_map)
{
	unit* obj = nullptr;
	if (m_targetID) obj = dynamic_cast<unit*> (_map->m_objects.get(m_targetID));
	bool trgExist (obj != nullptr && obj->isAlive());

	if (trgExist)
	{
		m_targetLastPos = obj->pos();
	}
	if (moveTo(m_targetLastPos))
	{
		if (trgExist)
		{
			obj->damage(m_damage);
			if (!obj->isAlive()) _map->m_objects.erase(obj->ID());
		}
		_map->m_objects.erase(m_id);
	}
}

std::unique_ptr<td::object> td::shell::clone(size_t _id)
{
	auto obj = std::make_unique<shell>(shell(*this));
	obj->m_id = _id;
	return obj;
}

