
#ifndef HEIGHT3D_GUI_WINDOW_HPP
#define HEIGHT3D_GUI_WINDOW_HPP

#include <SDL2/SDL.h>

class Window {
	
	SDL_Window *mainwindow;
	SDL_GLContext maincontext;

public: 
	Window(int width, int height, const char* name);
	~Window();

	void redraw();
	void delay(int n);
};

#endif // HEIGHT3D_GUI_WINDOW_HPP
