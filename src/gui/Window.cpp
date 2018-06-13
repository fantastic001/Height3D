
#include "Window.hpp"

#include <core/common.hpp>

Window::Window(int width, int height, const char* name) 
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	mainwindow = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	maincontext = SDL_GL_CreateContext(mainwindow);
	
	SDL_GL_SetSwapInterval(1);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

}

Window::~Window() 
{
	SDL_DestroyWindow(mainwindow);
}

void Window::redraw() 
{
	SDL_GL_SwapWindow(mainwindow);
}

void Window::delay(int n) 
{
	SDL_Delay(n);
}

