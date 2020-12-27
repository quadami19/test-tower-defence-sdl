#include "../include/spawner.hpp"
#include "../include/object_storage.hpp"

namespace td
{

std::pair<size_t, td::object *> td::spawner::spawn()
{
	auto obj = m_prototype->clone(m_objectsPtr->nextID());
	return m_objectsPtr->put(std::move(obj));
}

}
