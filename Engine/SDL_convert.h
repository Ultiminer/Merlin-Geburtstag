#pragma once
#include <SDL.h>
#include "primitives.h"

inline SDL_FRect VecToRect(const fvec4d& rct)
{
	return {rct.x,rct.y,rct.w,rct.h};
}
