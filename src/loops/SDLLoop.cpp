
#include "SDLLoop.hpp"
#include <core/Event.hpp>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <SDL2/SDL.h>


SDLLoop::SDLLoop(Window* w) 
{
	//SDL_EnableUNICODE( 1 );
	window = w;
}

SDLLoop::~SDLLoop() 
{
}

void SDLLoop::handleEvents() 
{
	while( SDL_PollEvent( &event ) ) 
	{
		switch( event.type ) 
		{
			case SDL_KEYDOWN:
				onKeyPress(Event(event.key.keysym.scancode));
				break;
			case SDL_KEYUP:
				onKeyRelease(Event(event.key.keysym.scancode));
				break;
			case SDL_QUIT:
				this->quit();
				break;
		}
	}
	if (!isFinished()) {
		glClearColor ( 0.0, 0.0, 0.0, 1.0 );
		glClear ( GL_COLOR_BUFFER_BIT );
		window->redraw();
		window->delay(50);
	}
}
