
#ifndef HEIGHT3D_GUI_WINDOW_HPP
#define HEIGHT3D_GUI_WINDOW_HPP

#include <SDL2/SDL.h>

/// Represents SDL window to be used for drawing
class Window {
	
	SDL_Window *mainwindow;
	SDL_GLContext maincontext;

public: 
	/// Construct window with given width, height and name
	Window(int width, int height, const char* name);
	~Window();
	
	/// redraw contents of the window
	void redraw();

	/// ssleep for specified time (in ms)
	void delay(int n);
};

#endif // HEIGHT3D_GUI_WINDOW_HPP
