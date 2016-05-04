
#ifndef HEIGHT3D_LOOP_HPP
#define HEIGHT3D_LOOP_HPP

#include "Event.hpp"

class Loop 
{

	bool finished; 
public:
	void run(); 
	void quit(); 
	bool isFinished();

protected:
	// these methods are for implementation of derived loop classes 
	virtual void handleEvents() = 0; // should call all event methods except onInit and onQuit

	// these are event handling methods
	virtual void onInit() = 0;
	virtual void onKeyPress(Event e) = 0;
	virtual void onKeyRelease(Event e) = 0;
	virtual void onQuit() = 0;
	virtual void onFrame() = 0;

};

#endif // HEIGHT3D_LOOP_HPP
