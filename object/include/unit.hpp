#pragma once
#include <cmath>
#include <deque>
#include "object.hpp"

namespace td {

class unit : public object
{

		std::deque<SDL_Point> m_trajectory;

	public:

		unit(SDL_Texture* _tex, SDL_Point _pos, SDL_Point _size, size_t _id) : object(_tex, _pos, _size, _id) {}

		unit(const unit& _obj) :
			object(_obj),
			m_trajectory(_obj.m_trajectory)
		{}

		virtual ~unit() {}

		virtual void tick(map::general* _map) override;

		virtual std::unique_ptr<object> clone(size_t _id) override
		{
			auto obj = std::make_unique<unit>(unit(*this));
			obj->m_id = _id;
			return obj;
		}

		void trajectory(std::deque<SDL_Point> _traj)
		{
			m_trajectory = _traj;
		}
};

}
