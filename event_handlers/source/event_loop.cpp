#include <SDL2/SDL.h>
#include "../include/event_loop.hpp"
/*
Event_Loop::Event_Loop(Render_Loop *_ptr) :
	m_renderLoopPtr (_ptr)
{
	SDL_Event e;
	while (running) {
		while (SDL_PollEvent(&e)) {
			onEvent(&e);
		}
		m_renderLoopPtr->onLoop();
	}
}

Event_Loop::~Event_Loop()
{

}
#include <iostream>
void Event_Loop::onEvent(SDL_Event *_e) {
	switch (_e->type) {
		case SDL_KEYUP:
			break;
		case SDL_KEYDOWN:
			break;
		case SDL_MOUSEMOTION:
			onMouseMoved(&_e->motion);
			break;
		case SDL_MOUSEWHEEL:
			onMouseWheel(&_e->wheel);
			break;
		case SDL_QUIT:
			running = false;
			break;
		default:
			std::cout << _e->type << std::endl;
			break;
	}

}
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
void Event_Loop::onMouseMoved(SDL_MouseMotionEvent *_e)
{
	int dx = 0, dy = 0;
	if(_e->x + _e->xrel <= 0) dx = -5;
	if(_e->y + _e->yrel <= 0) dy = -5;
	if(_e->x + _e->xrel >= SCREEN_WIDTH) dx = 5;
	if(_e->y + _e->yrel >= SCREEN_HEIGHT) dy = 5;
	m_renderLoopPtr->camera().movePerTick(dx, dy);
}

void Event_Loop::onMouseWheel(SDL_MouseWheelEvent *_e)
{
	if (_e->y == -1) {
		m_renderLoopPtr->camera().rescale(0.95f, 0, 0);
	}
	else if (_e->y == 1) {
		m_renderLoopPtr->camera().rescale(1.05f, 0, 0);
	}
}

void Key_Events::pressed(SDL_KeyboardEvent *_e)
{
	m_pressed.push_back(_e->keysym);
}

void Key_Events::unpressed(SDL_KeyboardEvent *_e)
{
	for(size_t i = 0; i < m_pressed.size(); i++) {
		if (m_pressed[i].sym == _e->keysym.sym) {
			m_pressed.erase(m_pressed.begin() + i);
			return;
		}
	}
}
*/

bool td::events::build::checkRegion(SDL_MouseButtonEvent& _mbe)
{

}

void td::events::build::clear()
{
	m_isClickActive = false;
	m_isBuildActive = false;
}

bool td::events::build::handle(SDL_Event *_event)
{
	switch (_event->type) {
		case SDL_MOUSEBUTTONUP:
			if (m_isClickActive && !m_isBuildActive)
			{
				if(checkRegion(_event->button)) m_isBuildActive = true;
			}
			clear();
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(!m_isClickActive && !m_isBuildActive)
			{
				if(checkRegion(_event->button)) m_isClickActive = true;
			}
			clear();
			break;
	}
}
