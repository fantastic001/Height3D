
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
	/// should call all event methods except onInit and onQuit
	/// these methods are for implementation of derived loop classes 
	virtual void handleEvents() = 0; 

	/// Implement initialization stuff
	virtual void onInit() = 0;
	virtual void onKeyPress(Event e) = 0;
	virtual void onKeyRelease(Event e) = 0;

	/// Implement logic when destructor is called (animation finishes)
	virtual void onQuit() = 0;

	/// Implement drawing of objects on each frame event
	virtual void onFrame() = 0;

};

#endif // HEIGHT3D_LOOP_HPP
