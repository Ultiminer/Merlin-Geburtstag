#pragma once
#include "sprite.h"
#include "collisions.h"
#include <SDL.h>
#include "config.h"
#include <vector>
#include "readxml.h"
#include "exception_handling.h"




class Character
{
public:
	Character();
	Character(SDL_Renderer* renderer, SDL_Event* Event, size_t* delta_time, const int screen_width, SDL_Texture* image);
	~Character();
	fvec2d GetPos();
	float GetSpeed();
	void Draw();
	void Animate();
	void UpdateEvents();
	void SetHealth(const float health);
	float GetHealth();
	void SetX(const float x);
	void SetY(const float y);
	float GetHeight();
	float GetWidth();
	float GetY();
	float GetX();
	void SetDamage(const float dmg);
	float GetDamage();
	Rect GetBody();
	void SetBody(const Rect& bdy);
	Rect GetLowerHalf();
	Rect GetOffsetBody();
	void SetLowerHalf(const Rect& lwHlf);
	void SetCamera(const fvec2d& offset);
private:
	void QueryKeyInput();

	bool ANIMATION_DEFAULT=false;
	struct CHARACTER_VALUES {
		float health=0;
		float damage = 0;
		float speed = 0;
	}values;
	struct CHARACTER_CONTROLS{
		bool UP; bool LEFT; bool DOWN; bool RIGHT; bool SHOOT; bool STOP_SHOOT;
	}controls = { 0 }, prev_controls = { 0 };

	SDL_Event* Event=nullptr;
	SDL_Renderer* Renderer=nullptr;
	SDL_Texture* image=nullptr;
	size_t* delta_time=nullptr;
	Uint32 currentTicks = SDL_GetTicks();

	bool SwitchLR = false;
	bool SwitchUD = false;

	Sprite character;
};

