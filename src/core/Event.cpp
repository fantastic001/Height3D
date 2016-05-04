
#include "Event.hpp"

Event::Event(Key key) 
{
	m_key = key; 
}

Key Event::getKey() 
{
	return m_key; 
}
