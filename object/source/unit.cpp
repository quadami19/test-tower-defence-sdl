#include "../include/unit.hpp"
#include "../../map/include/map_general.hpp"

namespace td
{

void unit::tick(map::general *_map)
{
	if (m_trajectory.empty())
	{
		_map->m_objects.erase(m_id);
	}
	else
	{
		SDL_Point front = m_trajectory.front();
		if (moveTo(front)) m_trajectory.pop_front();
	}
}

}
