//#define BOOST_TEST_MODULE Functional_Event
#include <boost/test/unit_test.hpp>

#include <iostream>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include <loops/SDLLoop.hpp>
#include <core/Event.hpp>
#include "gui/Window.hpp"

using namespace std;

class MyLoop : public SDLLoop 
{

public:
	MyLoop(Window *w) : SDLLoop(w) 
	{

	}

protected:
	
	void onInit() 
	{
		glewInit();
	}

	void onKeyPress(Event e)
	{
		cout << "Pressed " << e.getKey().keycode << endl;
	}

	void onKeyRelease(Event e) 
	{
		cout << "Released " << e.getKey().keycode << endl;
	}

	void onQuit() {
		SDL_Quit();
	}


};

BOOST_AUTO_TEST_CASE( event )
{

	Window win(512, 512, "tutorial");
	MyLoop loop(&win);
	loop.run();
}


