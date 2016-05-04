
#ifndef HEIGHT3D_EVENT_HPP
#define HEIGHT3D_EVENT_HPP

typedef struct 
{
	char scancode; 
	char keycode; 
} Key; 

class Event {

	Key m_key; 

public:
	
	Event(Key key);

	Key getKey(); 

	bool operator==(Event e); 
	
};

#endif // HEIGHT3D_EVENT_HPP
