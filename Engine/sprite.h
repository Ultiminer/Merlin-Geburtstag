#pragma once 
#include <SDL.h>
#include "physics.h"
#include "exception_handling.h"
struct ANIMATION_SETUP { size_t ncols; size_t nrows; fvec2d pos; float fps; size_t crow; };

class Sprite
{
private:
	SDL_Texture* image;
	fvec4d body = { 0.0f };
	vec2d crop = { 0 };
	fvec2d camera = { 0 };
	SDL_Renderer* Renderer=nullptr;
	struct ROTATION { double angle; SDL_FPoint center;  SDL_RendererFlip flip; }rot{ 0 };
	ANIMATION_SETUP anim = { 1,1,{0,0}, 0,0 };
	uint32_t animTicks = SDL_GetTicks();

public:
	Sprite() { }
	Sprite(SDL_Renderer* rend) { this->Renderer = rend; }
	Sprite(SDL_Renderer* renderer, SDL_Texture* image) { this->Renderer = renderer; this->image = image; SDL_QueryTexture(image, NULL, NULL, &crop.w, &crop.h); }
	Sprite(SDL_Renderer* renderer, SDL_Texture* image, const fvec4d& body) { this->Renderer = renderer; this->image = image; SDL_QueryTexture(image, NULL, NULL, &crop.w, &crop.h);  this->body = body; }
	Sprite(SDL_Renderer* renderer, SDL_Texture* image, const fvec4d& body, const fvec2d& camera) { this->Renderer = renderer; this->image = image; SDL_QueryTexture(image, NULL, NULL, &crop.w, &crop.h); this->body = body; this->camera = camera; }
	~Sprite() {}


	void SetPos(const fvec2d& pos)
	{
		body.p1 = pos;
	}
	void SetPos(const float x, const float y)
	{
		body.p1={ x,y };
	}
	fvec2d GetPos()
	{
		return body.p1;
	}
	void Draw()
	{
		const SDL_FRect tbdy = { body.x - camera.x,body.y - camera.y,body.w,body.h };
		const SDL_Rect srect = {(int)(anim.pos.x),(int)(anim.pos.y),(int)(crop.w/anim.ncols),(int)(crop.h/anim.nrows)};
		SDL_RenderCopyExF(Renderer,image,&srect,&tbdy,rot.angle,&rot.center,rot.flip);
	}
	void SetCamera(const fvec2d& camera)
	{
		this->camera = camera;
	}
	fvec2d GetCamera()
	{
		return camera;
	}
	void Animate()
	{
		if (animTicks + 1000 / anim.fps > SDL_GetTicks())return;
		animTicks = SDL_GetTicks();
		anim.pos.x += (float)crop.w / anim.ncols;
		if (anim.pos.x >= crop.w)anim.pos.x = 0;
	}
	void ResetCropX()
	{
		anim.pos.x = 0;
	}
	void SetAnimation(const ANIMATION_SETUP& anim)
	{
		this->anim = anim;
		this->anim.pos.y = crop.h * static_cast<float>(this->anim.crow / this->anim.nrows);
	}
	void SetAnimation(const size_t ncols, const size_t nrows,const float fps)
	{
		this->anim = { ncols,nrows,{0,0},fps,0 };
		this->anim.pos.y = crop.h * static_cast<float>(this->anim.crow) / this->anim.nrows;
	}

	SDL_RendererFlip GetFlip() { return rot.flip; }
	void SetFlip(const SDL_RendererFlip& mode) { rot.flip = mode; }
	double GetAngle() { return rot.angle; }
	void SetAngle(const double angle) { rot.angle = angle; }
	void SetTexture(SDL_Texture* image) { this->image = image; SDL_QueryTexture(image, NULL, NULL, &crop.w, &crop.h); }
	void SetX(const float val) { body.x = val; }
	void SetY(const float val) { body.y = val; }
	void SetW(const float val) { body.w = val; }
	void SetH(const float val) { body.h = val; }

	float GetX() { return body.x; }
	float GetY() { return body.y; }
	float GetW() { return body.w; }
	float GetH() { return body.h; }

	inline void SetBody(const Rect& bdy)noexcept
	{
		body = bdy;
	}
	SDL_Renderer* GetRenderer()
	{
		return Renderer;
	}
	void ChangeRow(const size_t row)
	{
		anim.crow = row;
		anim.pos.y = crop.h * static_cast<float>(anim.crow) / anim.nrows;
	}
	size_t GetCurrentRow()const
	{
		return anim.crow;
	}
	Rect GetBody()
	{
		return body;
	}
	Rect GetOffsetBody()
	{
		return {body.x-camera.x,body.y-camera.y,body.w,body.h};
	}
};