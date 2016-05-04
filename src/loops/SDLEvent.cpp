

#include "SDLEvent.hpp"

bool SDLEvent::isKey(SDL_Keycode k) 
{
	Key m = getKey();
	return m.scancode == SDL_GetScancodeFromKey(k) && m.keycode == (char) k;
}
