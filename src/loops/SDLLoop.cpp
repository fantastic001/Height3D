
#include "SDLLoop.hpp"
#include "SDLEvent.hpp"

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
				Key k; 
				k.scancode = event.key.keysym.scancode;
				k.keycode = event.key.keysym.sym;
				onKeyPress(SDLEvent(k));
				break;
			case SDL_KEYUP:
				k.scancode = event.key.keysym.scancode;
				k.keycode = event.key.keysym.sym;
				onKeyRelease(SDLEvent(k));
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

