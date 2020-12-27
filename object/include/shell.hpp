#pragma once
#include "object.hpp"

namespace td
{

class shell : public object
{
		size_t m_targetID;
		SDL_Point m_targetLastPos;
		int m_damage = 20;

		void collision(object* _targ);

	public:
		shell(SDL_Texture* _tex, SDL_Point _pos, SDL_Point _size, size_t _id, size_t _targetID) :
			object(_tex, _pos, _size, _id),
			m_targetID(_targetID)
		{
			m_speed = 10;
		}

		shell(const shell& _obj) :
			object(_obj),
			m_targetID(0),
			m_targetLastPos({0, 0}),
			m_damage(_obj.m_damage)
		{}

		virtual ~shell() {}

		void setTarget(size_t _targetId) { m_targetID = _targetId; }

		virtual void tick(map::general *_map) override;
		virtual std::unique_ptr<object> clone(size_t _id) override;
};

}
