#pragma once
#include <math.h>
#include <vector>

constexpr float inv_root(const float number);

template <size_t m, size_t n>
struct fmat {
	union {
		float e[m * n];
	};
};

constexpr  float square(const float x) { return x * x; }
constexpr  float Croot(const float x) { return 1/inv_root(x); }
struct fvec2d { union { struct { float x; float y; }; struct { float r; float angle; }; struct { float w; float h; }; float n[2]; }; };
struct vec2d { union { int val[2]; struct { int x; int y; }; struct { int w; int h; }; }; };
struct vec4d { union { int val[4]; struct { int x; int y; int w; int h; }; }; };

struct fvec3d { 
	union {
		struct {
			float x; float y; float z;
		};
		struct {
			float x; float y; float r;
		};
		float n[3];
		struct {
			fvec2d p; float r;
		};

	};
};
struct fvec4d {
	union {
		struct {
			float x; float y; float z; float j;
		};
		struct {
			float x; float y; float w; float h;
		};
		struct {
			fvec2d p1; fvec2d p2;
		};
		struct {
			fvec3d v; float j;
		};
		float n[4];
	};
};
struct fvec6d {
	union {
		struct {
			float x1; float y1; float z1; float x2; float y2; float z2;
		};
		struct {
			fvec3d p1; fvec3d p2;
		};
		struct {
			fvec2d v1; fvec2d v2; fvec2d v3;
		};
		float n[6];
	};
};


typedef fvec6d Line3d;
typedef fvec3d Circle;
typedef fvec4d Line2d;
typedef fvec4d Rect;
typedef fvec4d Ellipse;

constexpr Circle EllipseToCircle(const Ellipse& e)
{
	return {e.x, e.y, (e.w+e.h)/2};
}
constexpr Ellipse CircleToEllipse(const Circle& c)
{
	return {c.x,c.y,c.r,c.r};
}
constexpr Rect LineToRect(const Line2d& l)
{
	return {l.x,l.y,l.p2.x-l.x,l.p2.y-l.y};
}
constexpr Rect CircleToRect(const Circle& c)
{
	return {c.x-c.r,c.y-c.r,c.r*2,c.r*2};
}
constexpr Rect EllipseToRect(const Ellipse& e)
{
	return{e.x-e.w,e.y-e.h,e.w*2,e.h*2};
}
constexpr Circle RectToCircle(const Rect& r)
{
	const float l = Croot(r.w * r.w + r.h * r.h) / 2;
	return { r.x + l, r.y + l, l };
}
constexpr Ellipse RectToEllipse(const Rect& r)
{
	return CircleToEllipse(RectToCircle(r));
}
constexpr Circle LineToCircle(const Line2d& l)
{
	const float r = Croot(square(l.p2.x - l.x) + square(l.p2.y - l.y));
	return {(l.x+l.p2.x)/2, (l.y+l.p2.y)/2, r};
}

constexpr fvec6d Addition2c(const fvec6d& a, const fvec6d& b)
{
	return {a.n[0]+b.n[0],a.n[1]+b.n[1],a.n[2],a.n[3],a.n[4],a.n[5]};
}
constexpr fvec4d Addition2c(const fvec4d& a, const fvec4d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1],a.n[2],a.n[3] };
}
constexpr fvec4d Addition2c(const fvec4d& a, const fvec2d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1],a.n[2],a.n[3] };
}
constexpr fvec3d Addition2c(const fvec3d& a, const fvec3d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1],a.n[2] };
}
constexpr fvec2d Addition2c(const fvec2d& a, const fvec2d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1]};
}
constexpr fvec6d Addition3c(const fvec6d& a, const fvec6d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1],a.n[2]+b.n[2],a.n[3],a.n[4],a.n[5] };
}
constexpr fvec4d Addition3c(const fvec4d& a, const fvec4d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1],a.n[2] + b.n[2],a.n[3] };
}
constexpr fvec3d Addition3c(const fvec3d& a, const fvec3d& b)
{
	return { a.n[0] + b.n[0],a.n[1] + b.n[1],a.n[2] + b.n[2] };
}

template<class FakeVec>
inline fvec2d ConvertToFVec2d(FakeVec v)
{
	return {static_cast<float>(v.x),static_cast<float>(v.y)};
}
template<class FakeVec>
inline vec2d ConvertToVec2d(FakeVec v)
{
	return { static_cast<int>(v.x),static_cast<int>(v.y) };
}
template<class FakeVec>
inline vec4d ConvertToVec4d(FakeVec v)
{
	return { static_cast<int>(v.x),static_cast<int>(v.y),static_cast<int>(v.w),static_cast<int>(v.h) };
}
template<class FakeVec>
inline fvec4d ConvertToFVec4d(FakeVec v)
{
	return { static_cast<float>(v.x),static_cast<float>(v.y),static_cast<float>(v.w),static_cast<float>(v.h) };
}
