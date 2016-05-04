
#ifndef HEIGHT3D_LOOPS_SDLEVENT_HPP
#define HEIGHT3D_LOOPS_SDLEVENT_HPP

#include <core/Event.hpp>

#include <SDL2/SDL.h>


class SDLEvent : public Event 
{

public:
	SDLEvent(Key k) : Event(k) {}

	bool isKey(SDL_Keycode k);
};

#endif // HEIGHT3D_LOOPS_SDLEVENT_HPP
