#pragma once
#include "../../object/include/object.hpp"
#include <unordered_map>
#include <deque>
#include <typeinfo>
#include <memory>

namespace td {
namespace map {

struct general;

struct object_storage
{
	private:

		std::unordered_map<size_t, std::unique_ptr<object>> m_objects;
		std::deque<size_t> m_eraseDeque;
		bool processing = false;
		size_t m_enumerator = 1;

		void flushErase()
		{
			for (auto i: m_eraseDeque)
			{
				m_objects.erase(m_objects.find(i));
			}
			m_eraseDeque.clear();
		}

	public:

		object_storage() {}

		size_t nextID()
		{
			return m_enumerator;
		}

		std::pair<size_t, object*> put(std::unique_ptr<object>&& _obj)
		{
			auto ptr = m_objects.insert(std::make_pair(m_enumerator, std::move(_obj)));
			return std::make_pair(m_enumerator++, ptr.first->second.get());
		}

		object* get(size_t _id)
		{
			auto obj = m_objects.find(_id);
			if (obj == m_objects.end()) return nullptr;
			else return obj->second.get();
		}

		static float get_distance(SDL_Point _p1, SDL_Point _p2)
		{
			_p1.x -= _p2.x;
			_p1.y -= _p2.y;
			return std::sqrt(_p1.x*_p1.x + _p1.y*_p1.y);
		}

		template<typename T>
		std::pair<size_t, object*> findNearest(SDL_Point& _point)
		{
			float dist = 0.f;
			auto i = m_objects.begin();
			auto f = m_objects.end();
			for (; i != m_objects.end(); i++)
			{
				auto& obj = i->second;
				if ((dist == 0.f || dist > get_distance(_point, obj->pos())) && dynamic_cast<T*>(obj.get()))
				{
					f = i;
				}
			}
			if (f == m_objects.end()) return std::make_pair(0, nullptr);
			else return std::make_pair(f->first, f->second.get());
		}

		bool erase(size_t _id)
		{
			auto tmp = m_objects.find(_id);

			if(tmp != m_objects.end())
			{
				if(processing) m_eraseDeque.push_back(_id);
				else m_objects.erase(tmp);
				return true;
			}
			else
			{
				return false;
			}
		}

		void render(SDL_Renderer* _renderer, SDL_Rect _camera)
		{
			for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
			{
				iter->second->render(_renderer, _camera);
			}
		}

		void tick(general* _map)
		{
			processing = true;
			for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
			{
				iter->second->tick(_map);
			}
			flushErase();
			processing = false;
		}
};

}
}
