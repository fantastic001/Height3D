
#include "Loop.hpp"

void Loop::run() 
{
	finished = false; 
	this->onInit();
	while (!finished) 
	{
		this->handleEvents();
	}
	this->onQuit();
	
}

void Loop::quit() 
{
	finished = true; 
}

bool Loop::isFinished() 
{
	return finished;
}
