

#include "SDLEvent.hpp"

bool SDLEvent::isKey(SDL_Keycode k) 
{
	Key m = getKey();
	return m.scancode == SDL_GetScancodeFromKey(k) && m.keycode == (char) k;
}

Event SDLEvent::asEvent(SDL_Keycode k) 
{
	Key m; 
	m.scancode = SDL_GetScancodeFromKey(k);
	m.keycode = (char) k;
	return Event(m);
}
