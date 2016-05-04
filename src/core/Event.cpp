
#include "Event.hpp"

Event::Event(char key) 
{
	m_key = key; 
}

char Event::getKeyCode() 
{
	return m_key; 
}
