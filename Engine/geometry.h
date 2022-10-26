#pragma once
#include "primitives.h"
#include <math.h>

constexpr double PI32 = 0.09817477042468103870195760572748;
constexpr float root2 = 1.4142f;
constexpr bool IsEven(const unsigned int n) { return (n / 2 == (n + 1) / 2); }
constexpr bool IsOdd(const unsigned int n) { return (n / 2 != (n + 1) / 2); }
constexpr const float fPI = 3.1415926535f;
//Support functions, projections, rotations, raycasting ...
constexpr const float epsilon = 0.00001f;




inline float average(const std::vector<float>& arr)
{
	float sum = 0;
	for (size_t i = 0; i < arr.size(); i++)sum += arr.at(i);
	return sum / arr.size();
}
constexpr float average(const float a, const float b)
{
	return (a + b) / 2;
}



constexpr float arg(const fvec2d& v)
{
	if (v.x > 0)return atanf(v.y / v.x);
	if (v.x < 0 && v.y>= 0)return atanf(v.y / v.x+fPI);
	if (v.x < 0 && v.y < 0)return atanf(v.y/v.x-fPI);
	if (v.x == 0 && v.y > 0)return fPI / 2;
	if (v.x == 0 && v.y < 0)return fPI / 2;
	return 0.0f;
}
constexpr float arg(const float x, const float y)
{
	if (x > 0)return atanf(y / x);
	if (x < 0 && y >= 0)return atanf(y / x + fPI);
	if (x < 0 && y < 0)return atanf(y / x - fPI);
	if (x == 0 && y > 0)return fPI / 2;
	if (x == 0 && y < 0)return fPI / 2;
	return 0.0f;
}
constexpr bool between(const float a, const float m, const float b)
{
	return (m > a) * (b > a);
}
constexpr float dotprod(const fvec6d& a, const fvec6d& b)
{
	return a.n[0] * b.n[0] + a.n[1] * b.n[1] + a.n[2] * b.n[2] + a.n[3] * b.n[3] + a.n[4] * b.n[4] + a.n[5] * b.n[5];
}
constexpr float dotprod(const fvec4d& a, const fvec4d& b)
{
	return a.n[0] * b.n[0] + a.n[1] * b.n[1] + a.n[2] * b.n[2] + a.n[3] * b.n[3];
}
constexpr float dotprod(const fvec3d& a, const fvec3d& b)
{
	return a.n[0] * b.n[0] + a.n[1] * b.n[1] + a.n[2] * b.n[2];
}
constexpr float dotprod(const fvec2d& a, const fvec2d& b)
{
	return a.n[0] * b.n[0] + a.n[1] * b.n[1];
}
constexpr fvec6d dotprod(const fvec6d& a, const float b)
{
	return { a.n[0] * b,a.n[1] * b,a.n[2] * b,a.n[3] * b,a.n[4] * b,a.n[5] * b };
}
constexpr fvec4d dotprod(const fvec4d& a, const float b)
{
	return { a.n[0] * b,a.n[1] * b,a.n[2] * b,a.n[3] * b };
}
constexpr fvec3d dotprod(const fvec3d& a, const float b)
{
	return { a.n[0] * b,a.n[1] * b,a.n[2] * b };
}
constexpr fvec2d dotprod(const fvec2d& a, const float b)
{
	return { a.n[0] * b,a.n[1] * b };
}
constexpr float dotprod(const float a, const float b)
{
	return a * b;
}

constexpr fvec3d multiply(const fmat<3, 3>& mat, const fvec3d& v)
{
	return { mat.e[0] * v.n[0] + mat.e[1] * v.n[1] + mat.e[2] * v.n[2],mat.e[3] * v.n[0] + mat.e[4] * v.n[1] + mat.e[5] * v.n[2],mat.e[6] * v.n[0] + mat.e[7] * v.n[1] + mat.e[8] * v.n[2] };
}
constexpr fvec2d multiply(const fmat<2, 2>& mat, const fvec2d& v)noexcept
{
	return { mat.e[0] * v.n[0] + mat.e[1] * v.n[1],mat.e[2] * v.n[0] + mat.e[3] * v.n[1] };
}
constexpr fmat<3, 3> multiply(const fmat<3, 3>& mat, const float b)
{
	return{mat.e[0]*b,mat.e[1] * b, mat.e[2] * b, mat.e[3] * b, mat.e[4] * b, mat.e[5] * b, mat.e[6] * b, mat.e[7] * b, mat.e[8] * b};
}
constexpr fmat<2, 2> multiply(const fmat<2, 2>& mat, const float b)
{
	return{ mat.e[0] * b,mat.e[1] * b, mat.e[2] * b, mat.e[3] * b };
}

constexpr fvec6d operator + (const fvec6d& a, const fvec6d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1],a.n[2] + b.n[2],a.n[3] + b.n[3],a.n[4] + b.n[4],a.n[5] + b.n[5] };
}
constexpr fvec4d operator + (const fvec4d& a, const fvec4d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1],a.n[2] + b.n[2],a.n[3] + b.n[3] };
}
constexpr fvec3d operator + (const fvec3d& a, const fvec3d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1],a.n[2] + b.n[2] };
}
constexpr fvec2d operator + (const fvec2d& a, const fvec2d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1] };
}
constexpr fvec6d operator - (const fvec6d& a, const fvec6d& b)
{
	return { a.n[0] - b.n[0],a.n[1] - b.n[1],a.n[2] - b.n[2],a.n[3] - b.n[3],a.n[4] - b.n[4],a.n[5] - b.n[5] };
}
constexpr fvec4d operator - (const fvec4d& a, const fvec4d& b)
{
	return { a.n[0] - b.n[0],a.n[1] - b.n[1],a.n[2] - b.n[2],a.n[3] - b.n[3] };
}
constexpr fvec3d operator - (const fvec3d& a, const fvec3d& b)
{
	return { a.n[0] - b.n[0],a.n[1] - b.n[1],a.n[2] - b.n[2] };
}
constexpr fvec2d operator - (const fvec2d& a, const fvec2d& b)
{
	return { a.n[0] - b.n[0],a.n[1] - b.n[1] };
}

constexpr fvec2d transpose(const fvec2d& v)
{
	return { v.y,v.x };
}
constexpr fvec3d transpose(const fvec3d& v)
{
	return { v.z,v.y,v.x };
}
constexpr fvec4d transpose(const fvec4d& v)
{
	return { v.w,v.z,v.y,v.x };
}
constexpr fvec6d transpose(const fvec6d& v)
{
	return { v.n[5],v.n[4],v.n[3],v.n[2],v.n[1],v.n[0] };
}
constexpr fmat<3, 3> transpose(const fmat<3, 3>& m)
{
	return { m.e[8],m.e[5],m.e[2],m.e[7],m.e[4],m.e[1],m.e[6],m.e[3],m.e[0] };
}
constexpr fmat<2, 2> transpose(const fmat<2, 2>& m)
{
	return { m.e[3],m.e[1],m.e[2],m.e[0] };
}

constexpr float length(const fvec2d& v)
{
	return Croot(dotprod(v, v));
}
constexpr float length(const fvec3d& v)
{
	return Croot(dotprod(v, v));
}
constexpr float length(const fvec4d& v)
{
	return Croot(dotprod(v, v));
}
constexpr float length(const fvec6d& v)
{
	return Croot(dotprod(v, v));
}
constexpr float length(const float a)
{
	return Croot(a*a);
}

constexpr float det(const float a, const float b, const float c, const float d)
{
	return (a * d - b * c);
}
constexpr float det(const fmat<2, 2>& m)
{
	return (m.e[0] * m.e[3] - m.e[1] * m.e[2]);
}
constexpr float det(const fmat<3, 3>& m)
{
	return m.e[0] * det(m.e[4], m.e[5], m.e[7], m.e[8]) - m.e[3] * det(m.e[1], m.e[2], m.e[7], m.e[8]) + m.e[6] * det(m.e[1], m.e[2], m.e[4], m.e[5]);
}

constexpr fvec6d inv(const fvec6d& v)
{
	return { -v.n[5],v.n[4],v.n[3],v.n[2],v.n[1],v.n[0] };
}
constexpr fvec4d inv(const fvec4d& v)
{
	return { -v.n[3],v.n[2],v.n[1],v.n[0] };
}
constexpr fvec3d inv(const fvec3d& v)
{
	return { -v.n[2],v.n[1],v.n[0] };
}
constexpr fvec2d inv(const fvec2d& v)
{
	return { -v.n[1],v.n[0] };
}
constexpr fmat<2, 2> inv(const fmat<2,2>& m)
{
	const fmat<2, 2> d = { m.e[3],-m.e[1],-m.e[2],m.e[0] };
	return multiply(d,1/det(m));
}

constexpr float squaredist(const fvec2d& a, const fvec2d& b)
{
	return square(a.x - b.x) + square(a.y-b.y);
}
constexpr float squaredist(const fvec3d& a, const fvec3d& b)
{
	return square(a.x - b.x) + square(a.y - b.y)+square(a.z-b.z);
}
constexpr float squaredist(const fvec4d& a, const fvec4d& b)
{
	return square(a.x - b.x) + square(a.y - b.y)+square(a.z-b.z)+square(a.w-b.w);
}
constexpr float squaredist(const fvec6d& a, const fvec6d& b)
{
	return square(a.n[0]-b.n[0])+ square(a.n[1] - b.n[1]) + square(a.n[2] - b.n[2]) + square(a.n[3] - b.n[3]) + square(a.n[4] - b.n[4]) + square(a.n[5] - b.n[5]);
}

constexpr float inv_root(const float number)
{
	long i=0;
	float x2=0, y=0;
	const float thf = 1.5f;
	x2 = number * 0.5f;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (thf - (x2 * y * y));
	return y;
}
constexpr fvec2d projection(const fvec2d& a, const fvec2d& b)
{
	return dotprod(b,dotprod(a,b)/dotprod(b,b));
}
constexpr fvec3d projection(const fvec3d& a, const fvec3d& b)
{
	return dotprod(b, dotprod(a, b) / dotprod(b, b));
}
constexpr fvec4d projection(const fvec4d& a, const fvec4d& b)
{
	return dotprod(b, dotprod(a, b) / dotprod(b, b));
}
constexpr fvec6d projection(const fvec6d& a, const fvec6d& b)
{
	return dotprod(b, dotprod(a, b) / dotprod(b, b));
}

constexpr float cosf(const fvec2d& a, const fvec2d &b)
{
	return dotprod(a, b) * inv_root(dotprod(a,a)*dotprod(b,b));
}
constexpr float cosf(const fvec3d& a, const fvec3d& b)
{
	return dotprod(a, b) * inv_root(dotprod(a, a) * dotprod(b, b));
}
constexpr float cosf(const fvec4d& a, const fvec4d& b)
{
	return dotprod(a, b) * inv_root(dotprod(a, a) * dotprod(b, b));
}
constexpr float cosf(const fvec6d& a, const fvec6d& b)
{
	return dotprod(a, b) * inv_root(dotprod(a, a) * dotprod(b, b));
}
constexpr fvec2d normalize(const float x, const float y)
{
	const fvec2d v = { x,y };
	return dotprod(v, inv_root(dotprod(v, v)));
}
constexpr fvec2d normalize(const fvec2d& v)
{
	return dotprod(v,inv_root(dotprod(v,v)));
}
constexpr fvec4d normalize(const fvec4d& v)
{
	return dotprod(v, inv_root(dotprod(v, v)));
}
constexpr fvec3d normalize(const fvec3d& v)
{
	return dotprod(v, inv_root(dotprod(v, v)));
}
constexpr fvec6d normalize(const fvec6d& v)
{
	return dotprod(v, inv_root(dotprod(v, v)));
}
constexpr fvec2d normalize(const fvec2d& a, const fvec2d& b)
{
	return normalize(b-a);
}
constexpr fvec3d normalize(const fvec3d& a, const fvec3d& b)
{
	return normalize(b - a);
}
constexpr fvec4d normalize(const fvec4d& a, const fvec4d& b)
{
	return normalize(b - a);
}
constexpr fvec6d normalize(const fvec6d& a, const fvec6d& b)
{
	return normalize(b - a);
}

constexpr float crossprod(const fvec2d&a, const fvec2d& b)
{
	return a.x * b.y - b.x * a.y;
}
constexpr fvec3d crossprod(const fvec3d& a, const fvec3d& b)
{
	return {a.n[1]*b.n[2]-a.n[2]*b.n[1],a.n[2]*b.n[0]-a.n[0]*b.n[2],a.n[0]*b.n[1]-a.n[1]*b.n[0]};
}

constexpr float sinf(const fvec2d&a, const fvec2d& b)
{
	return length(crossprod(a, b))*inv_root(dotprod(a,a)*dotprod(b,b));
}
constexpr float sinf(const fvec3d& a, const fvec3d& b)
{
	return length(crossprod(a, b)) * inv_root(dotprod(a, a) * dotprod(b, b));
}

inline fmat<2, 2> rot2d(const float angle)
{
	return {cosf(angle),-sinf(angle),sinf(angle),cosf(angle)};
}
inline fmat<3, 3> rot3d(const float alpha, const float beta, const float gamma)
{
	return { cosf(alpha) * cosf(beta) * cosf(gamma) - sinf(alpha) * sinf(gamma), -cosf(alpha) * cosf(beta) * sinf(gamma) - sinf(alpha) * cosf(gamma),cosf(alpha) * sinf(beta),sinf(alpha) * cosf(beta) * cosf(gamma) + cosf(alpha) * sinf(gamma),-sinf(alpha) * cosf(beta) * sinf(gamma) + cosf(alpha) * cosf(gamma),sinf(alpha) * sinf(beta),-sinf(beta) * cosf(gamma),sinf(beta) * sinf(gamma),cosf(beta) };
}
inline fvec2d rotate(const fvec2d& v, const float angle, const fvec2d& p)
{
	const float X = v.x - p.x; const float Y = v.y - p.y;
	return {p.x+cosf(angle)*X-sinf(angle)*Y,p.y+sinf(angle)*X+cosf(angle)*Y};
}
inline fvec2d rotate(const fvec2d& v, const float angle)
{
	return { cosf(angle) * v.x - sinf(angle) * v.y,sinf(angle) * v.x + cosf(angle) * v.y };
}
inline Line2d rotate(const Line2d& l,const float angle, const fvec2d& p)
{
	Line2d l0 = { 0 }; l0.p1 = rotate(l.p1, angle, p); l0.p2 = rotate(l.p2, angle, p);
	return l0;
}
constexpr fvec3d express3d(const fvec2d& v)
{
	return {v.x,v.y,0};
}

inline fvec2d PolarToCart(const fvec2d& v)
{
	const fvec2d R = { v.x * cosf(v.y),v.x * sinf(v.y) };
	return R;
}

constexpr fvec2d CartToPolar(const fvec2d& v)
{
	return { Croot(dotprod(v.x,v.y)),arg(v)};
}