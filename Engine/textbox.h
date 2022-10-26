#pragma once
#include "Sprite.h"
#include <SDL_ttf.h>



class MGE_STD_TEXTBOX
{
private:
	SDL_Color text_color = { 255,255,255,255 };
	TTF_Font* font = nullptr; 
	SDL_Renderer* renderer=nullptr;
	SDL_Texture* font_texture = nullptr;
	SDL_FRect box = { 0,0,0,25};
	SDL_FRect region = {0};
	float limit = 500;
	bool bg_visible=true;
	std::string text;
public:
	MGE_STD_TEXTBOX() {}
	MGE_STD_TEXTBOX(SDL_Renderer* renderer) { this->renderer = renderer; TTF_Init();font=TTF_OpenFont("../src/fonts/coure.fon", 80); }
	MGE_STD_TEXTBOX(SDL_Renderer* renderer, const SDL_FRect& box, const SDL_Color& color, const float limit, const bool bg_visible) { this->renderer = renderer; TTF_Init(); font = TTF_OpenFont("../src/fonts/coure.fon", 80); this->text_color = color; this->box = box; this->bg_visible = bg_visible; this->limit = limit; }

	~MGE_STD_TEXTBOX() { SDL_DestroyTexture(font_texture); TTF_CloseFont(font); TTF_Quit(); }
	void set_limit(const float limit) { this->limit = limit; }
	void set_position(const float x, const float y) { box.x= x; box.y=y; }
	void set_width(const float w) { box.w = w; }
	void set_height(const float h) { box.h = h; }
	void set_box(const SDL_FRect& box) { this->box = box; }
	void visible_bg(bool var) { bg_visible = var; }
	void set_text_color(const unsigned char r, const unsigned char g, const unsigned char b) { text_color = {r,g,b,255}; }
	void draw()
	{
		SDL_Color color;
		SDL_GetRenderDrawColor(renderer,&color.r,&color.g,&color.b,&color.a);
		if(bg_visible){
		SDL_SetRenderDrawColor(renderer,0,0,0,100);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRectF(renderer,&box);
		}
		SDL_RenderCopyF(renderer,font_texture,NULL,&box);
		SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	}
	void set_text(const std::string& text)
	{
		this->text = text;
		SDL_DestroyTexture(font_texture);
		SDL_Surface* font_surface = TTF_RenderText_Solid(font,text.c_str(),text_color);
		font_texture = SDL_CreateTextureFromSurface(renderer,font_surface);
		SDL_FreeSurface(font_surface);
		
		box.w = text.size() * 10.0f;
		if (box.w > limit)box.w = limit;
	}
	void clear_text() {this->text = ""; }
	void add_text(const std::string& text) { this->text += text; set_text(this->text); }
	float get_width()const
	{
		return box.w;
	}
};
