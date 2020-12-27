#pragma once
#include <SDL2/SDL.h>

#include <vector>
/*
#include "../../render/include/render_loop.hpp"
union SDL_Event;
struct SDL_MouseMotionEvent;
struct SDL_KeyboardEvent;
struct SDL_Keysym;

class Event_Loop
{
		Render_Loop* m_renderLoopPtr;
		bool running = true;
	public:
		Event_Loop(Render_Loop* _ptr);
		~Event_Loop();

		void onEvent(SDL_Event* _e);
		void onMouseMoved(SDL_MouseMotionEvent* _e);
		void onMouseWheel(SDL_MouseWheelEvent* _e);
};

class Key_Events
{
	std::vector<SDL_Keysym> m_pressed;
	public:
		Key_Events();
		~Key_Events();

		void pressed(SDL_KeyboardEvent* _e);
		void unpressed(SDL_KeyboardEvent* _e);
};

*/

namespace td {
namespace events {


class base
{
	public:
		base() {}

		virtual bool handle(SDL_Event* _event) = 0;
};

class build : public base
{
		bool m_isClickActive = false;
		bool m_isBuildActive = false;

		SDL_Rect m_zone;
		SDL_Texture* m_texture;

		bool checkRegion(SDL_MouseButtonEvent &_mbe);
		void clear();

	public:

		build(SDL_Rect _zone) : base(), m_zone(_zone) {}
		virtual bool handle(SDL_Event *_event) override;

};

class event_handler
{

	public:

		void onEvent(SDL_Event* _e);
};

}
}
