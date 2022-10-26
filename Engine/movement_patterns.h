#pragma once
#include "physics.h"

namespace MOVEMENT {
	inline void STRAIGHT(fvec2d& projectile, const fvec2d& target, const float dt, const float speed=1)
	{
		projectile= projectile+dotprod(normalize(projectile, target),speed*dt);
	}
	inline void ATRRACTIVE(fvec2d& projectile, fvec2d& projectile_velocity, const fvec2d& target, const float dt, const float attraction = 1)
	{
		ApplyAccel(projectile,projectile_velocity,Attraction(projectile,target,attraction),dt);
	}
	inline void MIRROR(fvec2d& projectile, const fvec2d& target, const fvec2d& reference, const float angle=fPI)
	{
		float r = Croot(squaredist(target,reference));
		projectile.x = reference.x + r * cosf(angle);
		projectile.y = reference.y + r * sinf(angle);
	}
}