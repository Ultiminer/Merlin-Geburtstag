#pragma once
#include "geometry.h"
#include <math.h>

constexpr bool PvP(const fvec2d& a, const fvec2d& b)
{
	return squaredist(a,b) < epsilon;
}
constexpr bool PvP(const fvec3d& a, const fvec3d& b)
{
	return squaredist(a, b) < epsilon;
}
constexpr bool PvP(const fvec4d& a, const fvec4d& b)
{
	return squaredist(a, b) < epsilon;
}
constexpr bool PvP(const fvec6d& a, const fvec6d& b)
{
	return squaredist(a, b) < epsilon;
}

constexpr bool RvR(const Rect& a, const Rect& b)
{
	return (a.x + a.w > b.x && b.x + b.w > a.x && a.y + a.h > b.y && b.y + b.h > a.y);
}
constexpr bool CvC(const Circle& a, const Circle& b)
{
	return squaredist(a.p, b.p) < square(a.r + b.r);
}
constexpr bool PvL(const fvec2d& p, const Line2d& b)
{
	const fvec2d A = b.p1 - p; const fvec2d B = b.p2 - p;
	const float dp = dotprod(A, B);
	return (square(dp)==dotprod(A,A)*dotprod(B,B)&&dp<0);
}
constexpr bool PvC(const fvec2d& p, const Circle& c)
{
	return squaredist(p,c.p)<square(c.r);
}
constexpr bool LvL(const Line2d& a, const Line2d& b)
{
	if (!RvR(LineToRect(a), LineToRect(b)))return false;
	const float dx1 = a.p2.x - a.p1.x, dy1 = a.p2.y - a.p1.y, dx2 = b.p2.x - b.p1.x, dy2 = b.p2.y - b.p1.y;
	if (dx1 * dx2 == 0)return true;
	if (dx1 * dy2 == dx2 * dy1)return PvL(a.p1,b);
	const float k1 = dy1 / dx1; const float k2 = dy2 / dx2;
	const float d1 = a.p1.y - a.p1.x * k1; const float d2 = b.p1.y - b.p1.x * k2;
	const float X = ((d2-d1)/(k1-k2));
	const float Y = X * k1 + d1;
	return PvL({ X,Y },b)* PvL({ X,Y }, a);
}
/*p gets filled with the point of intersection if the two lines intersect*/
inline bool IsectLine(const Line2d& a, const Line2d& b, fvec2d& point)
{
	if (!RvR(LineToRect(a), LineToRect(b)))return false;

	const float dx1 = a.p2.x - a.p1.x, dy1 = a.p2.y - a.p1.y, dx2 = b.p2.x - b.p1.x, dy2 = b.p2.y - b.p1.y;
	if (dx1 * dx2 == 0) { return true; }
	if (dx1 * dy2 == dx2 * dy1) { point = a.p1;if (PvL(a.p1, b)) {  return true; } return false; }
	const float k1 = dy1 / dx1; const float k2 = dy2 / dx2;
	const float d1 = a.p1.y - a.p1.x * k1; const float d2 = b.p1.y - b.p1.x * k2;
	const float X = ((d2 - d1) / (k1 - k2));
	const float Y = X * k1 + d1;
	point = { X,Y };
	return PvL({ X,Y }, b) * PvL({ X,Y }, a);
}

inline Rect ResRvR(const Rect& obj, const Rect& obstacle, const float alpha=5)
{
	if (!RvR(obj, obstacle))return obj;
	Rect dummy = obj;
	const Rect up = { obstacle.x+ alpha,obstacle.y,obstacle.w-2* alpha,obstacle.h/2 }, down = { obstacle.x+ alpha,obstacle.y + obstacle.h/2,obstacle.w-2* alpha,obstacle.h/2 }, left = { obstacle.x,obstacle.y+ alpha,alpha,obstacle.h-2* alpha }, right = {obstacle.x+obstacle.w-alpha,obstacle.y+ alpha,alpha,obstacle.h-2* alpha };
	if (RvR(obj, up)) dummy.y = obstacle.y - obj.h; 
	if (RvR(obj, down)) dummy.y = obstacle.y+obstacle.h; 
	if (RvR(obj, left)) dummy.x = obstacle.x - obj.w; 
	if (RvR(obj, right)) dummy.x = obstacle.x + obstacle.w;

	return dummy;
}