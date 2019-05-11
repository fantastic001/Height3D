
#ifndef HEIGHT3D_LOOPS_SDLLOOP_HPP
#define HEIGHT3D_LOOPS_SDLLOOP_HPP

#include <core/Loop.hpp>

#include <SDL2/SDL.h>
#include <gui/Window.hpp>

/// Loop class which redraws SDL Window on every frame
class SDLLoop : public Loop{

	SDL_Event event;
	Window* window; 
public:
	/// Construct SDL loop for given SDL Window
	SDLLoop(Window *w);
	~SDLLoop();

protected:
	void handleEvents();

};

#endif // HEIGHT3D_LOOPS_SDLLOOP_HPP
