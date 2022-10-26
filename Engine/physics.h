#pragma once 
#include "geometry.h"

typedef float mass;
typedef fvec2d vel2f;
typedef fvec3d vel3f;
typedef fvec2d accel2f;
typedef fvec3d accel3f;
typedef fvec2d impuls2f;
typedef fvec3d impuls3f;
typedef fvec2d force2f;
typedef fvec3d force3f;

enum class DEGFREE8 {
	DEFAULT,R, UR, U, UL, L, DL, D, DR
};

struct mpoint2f
{
	union{
		struct { float x; float y; float m; };
		struct { fvec2d p; float m; };
	};
};
struct mpoint3f
{
	union {
		struct { float x; float y; float z; float m; };
		struct { fvec3d p; float m; };
	};
};


inline mass TotalMass(const std::vector<mpoint2f>& points)
{
	mass m0=0;
	for (size_t i = 0; i < points.size(); i++)m0 += points.at(i).m;
	return m0;
}
inline mass TotalMass(const std::vector<mpoint3f>& points)
{
	mass m0 = 0;
	for (size_t i = 0; i < points.size(); i++)m0 += points.at(i).m;
	return m0;
}
/*Multiplies all masses together*/
inline mass MassProduct(const std::vector<mpoint2f>& points)
{
	mass m0 = 1;
	for (size_t i = 0; i < points.size(); i++)m0 *= points.at(i).m;
	return m0;
}
inline mass MassProduct(const std::vector<mpoint3f>& points)
{
	mass m0 = 1;
	for (size_t i = 0; i < points.size(); i++)m0 *= points.at(i).m;
	return m0;
}
inline mass ReducedMass(const std::vector<mpoint2f>& points)
{
	return MassProduct(points) / TotalMass(points);
}
inline mass ReducedMass(const std::vector<mpoint3f>& points)
{
	return MassProduct(points) / TotalMass(points);
}
/*Returns a mass_point containing the center of mass as its coordinates and the reduced mass as its mass*/
inline mpoint2f CenterOfMass(const std::vector<mpoint2f>& points)
{
	mpoint2f p0 = { 0 };
	for (size_t i = 0; i < points.size(); i++)p0.p = p0.p+dotprod(points.at(i).p,points.at(i).m);
	p0.m = ReducedMass(points);
	return p0;
}
inline mpoint3f CenterOfMass(const std::vector<mpoint3f>& points)
{
	mpoint3f p0 = { 0 };
	for (size_t i = 0; i < points.size(); i++)p0.p = p0.p + dotprod(points.at(i).p, points.at(i).m);
	p0.m = ReducedMass(points);
	return p0;
}

class ForceSystem
{
private:
	std::vector <force3f*> forces3d;
	std::vector <force2f*> forces2d;
	force3f sum = { 0.0f };
	force3f prev_sum = { 0.0f };

public:
	ForceSystem(){}
	~ForceSystem() {}
	size_t Add(force3f* force) { forces3d.push_back(force); return 2*forces3d.size()+1; }
	size_t Add(force2f* force) { forces2d.push_back(force); return 2*forces2d.size();}
	void Clear() { forces3d.clear(); forces2d.clear(); sum = { 0 }; }
	void Clear(const size_t id) { if (IsEven(id)) { forces2d.erase(forces2d.begin() + id / 2 - 1); return; } forces3d.erase(forces3d.begin()+(id-1)/2-1); }
	void Update() { prev_sum = sum; sum = { 0 }; for (size_t i = 0; i < forces3d.size(); i++)sum = sum + *forces3d.at(i); for (size_t i = 0; i < forces2d.size(); i++)sum = sum + express3d(*forces2d.at(i)); }
	fvec3d GetTotal() { return sum; }
	fvec2d GetTotal2d() { return { sum.x,sum.y }; }
	fvec3d GetPrevTotal() { return prev_sum; }
	fvec2d GetPrevTotal2d() { return { prev_sum.x,prev_sum.y }; }
};

constexpr float kinEnergy(const mass m, const float v)
{
	return 0.5f * dotprod(v, v) * m;
}
constexpr float kinEnergy(const mass m, const vel2f& v)
{
	return 0.5f * dotprod(v, v) * m;
}
constexpr float kinEnergy(const mass m, const vel3f& v)
{
	return 0.5f * dotprod(v, v) * m;
}

constexpr force3f Gravity(const mpoint3f& p1, const mpoint3f& p2, const float k=0.001)
{
	const fvec3d& r = p1.p - p2.p;
	return dotprod(normalize(r) , k*p1.m*p2.m/dotprod(r,r));
}

constexpr force2f Gravity(const mpoint2f& p1, const mpoint2f& p2, const float k = 0.001)
{
	const fvec2d& r = p1.p - p2.p;
	return dotprod(normalize(r), k * p1.m * p2.m / dotprod(r, r));
}
constexpr accel2f Attraction(const fvec2d& p1, const fvec2d& p2, const float K = 0.001)
{
	const fvec2d& r = p1 - p2;
	return dotprod(normalize(r), K / dotprod(r, r));
}
constexpr accel3f Attraction(const fvec3d& p1, const fvec3d& p2, const float K = 0.001)
{
	const fvec3d& r = p1 - p2;
	return dotprod(normalize(r), K / dotprod(r, r));
}
constexpr force3f Spring(const mpoint3f& p, const mpoint3f& p0, const float k = 0.001)
{
	const fvec3d& r = p0.p - p.p;
	return dotprod(r,k);
}
constexpr force2f Spring(const mpoint2f& p, const mpoint2f& p0, const float k = 0.001)
{
	const fvec2d& r = p0.p - p.p;
	return dotprod(r, k);
}
constexpr float Spring(const float x, const float x_0, const float k= 0.001)
{
	return (x_0 - x) * k;
}
inline void ApplyForce(mpoint3f& p, vel3f& v, const force3f& F, const float dt=1 )
{
	p.p = p.p + dotprod(v,dt)+dotprod(F,0.5f*square(dt)/p.m);
	v = v + dotprod(F,dt/p.m);
}
inline void ApplyForce(mpoint2f& p, vel2f& v, const force2f& F, const float dt = 1)
{
	p.p = p.p + dotprod(v, dt) + dotprod(F, 0.5f * square(dt) / p.m);
	v = v + dotprod(F, dt / p.m);
}
inline void ApplyAccel(fvec2d& p, vel2f& v, const fvec2d& a, const float dt = 1)
{
	p = p + dotprod(v, dt) + dotprod(a, 0.5f * square(dt) );
	v = v + dotprod(a, dt);
}
inline void ApplyAccel(fvec3d& p, vel3f& v, const fvec3d& a, const float dt = 1)
{
	p = p + dotprod(v, dt) + dotprod(a, 0.5f * square(dt));
	v = v + dotprod(a, dt);
}
constexpr fvec3d Torque(const fvec3d& r, const force3f& F)
{
	return crossprod(r, F);
}
constexpr fvec3d angMoment(const fvec3d& r, const impuls3f& p)
{
	return crossprod(r, p);
}
constexpr float Torque(const fvec2d& r, const force2f& F)
{
	return crossprod(r, F);
}
constexpr float angMoment(const fvec2d& r, const impuls2f& p)
{
	return crossprod(r, p);
}
inline float Torque(const float r, const float F, const float angle)
{
	return r*F * sinf(angle);
}
inline float angMoment(const float r, const float p, const float angle)
{
	return r*p * sinf(angle);
}
constexpr float InertiaRect(const float w, const float h, const float m)
{
	return 0.083f * m * (square(w) + square(h));
}
constexpr float InertiaCircle(const float m, const float r)
{
	return 0.5f * m * square(r);
}
constexpr float InertiaLine(const float x1, const float x2, const float y1, const float y2, const float m)
{
	const float r2 = square(x1-x2)+square(y1-y2);
	return 0.083f * m * r2;
}
inline float RotAngle(float& angularvel, const fvec3d& r, const force3f &F, const float inertia, const float dt)
{
	const float D = length(crossprod(r, F)) / inertia;
	const float angle = angularvel * dt + 0.5f * D * dt;
	angularvel += D * dt;
	return angle;
}
inline float RotAngle(float& angularvel, const fvec2d& r, const force2f& F, const float inertia, const float dt)
{
	const float D = length(crossprod(r, F)) / inertia;
	const float angle = angularvel * dt + 0.5f * D * dt;
	angularvel += D * dt;
	return angle;
}


inline Rect UniMovRect(const Rect& obj, const float speed, const DEGFREE8& direction, const size_t dt=0)
{
	Rect R=obj;
	switch (direction)
	{
	case DEGFREE8::R: R.x += speed * dt; break;
	case DEGFREE8::L: R.x -= speed * dt; break;
	case DEGFREE8::U: R.y -= speed * dt; break;
	case DEGFREE8::D: R.y += speed * dt; break;
	case DEGFREE8::UR:  R.y -= speed * dt*inv_root(2); R.x += speed * dt * inv_root(2); break;
	case DEGFREE8::UL:  R.y -= speed * dt * inv_root(2); R.x -= speed * dt * inv_root(2); break;
	case DEGFREE8::DR:  R.y += speed * dt * inv_root(2); R.x += speed * dt * inv_root(2); break;
	case DEGFREE8::DL:  R.y += speed * dt * inv_root(2); R.x -= speed * dt * inv_root(2); break;
	}

	return R;
}