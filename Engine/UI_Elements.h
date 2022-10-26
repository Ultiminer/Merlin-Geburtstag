#pragma once
#include "sprite.h"
#include "textbox.h"
class Healthbar {
private:
	Sprite sprite;
	SDL_FRect bar = { 0 };
	unsigned char mana=0;
	unsigned char max_mana = 0;
	bool DEATH = false;
	unsigned char damage=0;
	SDL_FRect bg = { 0 };
public:
	Healthbar() {};
	Healthbar(SDL_Renderer* renderer, SDL_Texture* image, const fvec4d& body, const unsigned char maxMana) { max_mana = maxMana; sprite = Sprite(renderer, image, body); bar = { body.x + body.w * 2 / 9,body.y + body.h / 4,body.w * 3 / 4,body.h * 2 / 3 }; sprite.SetAnimation(1, 4,  20); bg = bar; };
	~Healthbar() {};
	void SetMana(const unsigned char mana)
	{
		this->mana = mana;
	}
	unsigned char GetMana()const
	{
		return mana;
	}
	void Damage()
	{
		if (damage > 2) { DEATH = true; return; }
		damage++;
		sprite.ChangeRow(damage);
	}
	void Draw()
	{
		SDL_SetRenderDrawColor(sprite.GetRenderer(), 255,255, 255, 255);
		SDL_RenderFillRectF(sprite.GetRenderer(), &bg);
		SDL_SetRenderDrawColor(sprite.GetRenderer(), 10, 10, 255, 255);
		bar.w = sprite.GetW()*3/4 * mana / max_mana;
		SDL_RenderFillRectF(sprite.GetRenderer(), &bar);
		sprite.Animate();
		sprite.Draw();
	}
	unsigned char GetDamage()const
	{
		return damage;
	}
};

class EditField{
private:
	MGE_STD_TEXTBOX* textbox;
	SDL_Renderer* renderer;
	SDL_Event* sdlEvent;
	SDL_FRect body;
	std::string text;
	Uint32 timer = 0;
public:
	EditField() { body = { 0 }; sdlEvent = nullptr; renderer = nullptr; textbox = nullptr; }
	EditField(SDL_Renderer* renderer, SDL_Event* sdlEvent, const SDL_FRect& body) { this->body = body;  this->renderer = renderer; this->sdlEvent = sdlEvent; textbox = new MGE_STD_TEXTBOX(renderer, { body.x + 10, body.y + 10,body.w - 20,body.h - 20 }, { 0,0,0,0 },body.w-20,false);}
	~EditField() { delete textbox; }
	void draw() { SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200); SDL_RenderFillRectF(renderer, &body); textbox->draw();  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); SDL_RenderDrawRectF(renderer,&body); }
	const char* getText()const { return text.c_str(); }
	void listen() { if (timer + 100 > SDL_GetTicks())return; if (sdlEvent->type != SDL_KEYDOWN)return; const char c = sdlEvent->key.keysym.sym; if (c > 31) text += c; else if (c == SDLK_BACKSPACE&&text.size()!=0) { text.pop_back(); timer = SDL_GetTicks(); } textbox->set_text(text.c_str()); }
	void clear() { text.erase(text.begin(),text.end()); }
};

