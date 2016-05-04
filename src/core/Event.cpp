
#include "Event.hpp"

Event::Event(Key key) 
{
	m_key = key; 
}

Key Event::getKey() 
{
	return m_key; 
}

bool Event::operator==(Event e) 
{
	Key k = e.getKey();
	return m_key.scancode == k.scancode && m_key.keycode == k.keycode;
}
