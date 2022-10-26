#pragma once

#include "geometry.h"
#include "SDL_convert.h"

class Camera
{
private:
	fvec2d offset = { 0 };
	fvec2d screen_mid = { 0 };
	float r_max = 0.0f;
public:
	Camera() {}
	Camera(const fvec2d& window_size, const fvec2d& init_pos = { 0,0 })
	{ 
		offset = init_pos; 
		screen_mid = {window_size.x/2,window_size.y/2};
		r_max = length(window_size) /14;
	}
	~Camera() {}
	float GetX() { return offset.x; }
	float GetY() { return offset.y; }
	fvec2d GetPos() { return offset; }
	void Add(const fvec2d& o) { offset = {offset.x+o.x,offset.y+o.y}; }
	void SetX(const float x) { offset.x = x; }
	void SetY(const float y) { offset.y = y; }
	void SetPos(const fvec2d& v) { offset = v; }
	void ObjUpdate(const Rect& obj, const float speed)
	{
		const fvec2d tobj= obj.p1 - offset-screen_mid+dotprod(obj.p2,0.5f);
		const float r = length(tobj);
		if (r < r_max)return;
		const fvec2d n = normalize(tobj);
		offset = offset+dotprod(n,speed);
	}
};