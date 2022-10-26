#ifndef LABEL_H_
#define LABEL_H_ LABEL_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

#pragma warning (disable : 4838 4244 4018)
inline SDL_Texture* LoadTextureFromFont(const char* font, const int ptsize, SDL_Renderer* r)
{
	std::string cstring;
	for (int i = 32; i < 126; i++)cstring.push_back(i);
	TTF_Init();
	TTF_Font*f=TTF_OpenFont(font, ptsize);
	SDL_Surface* foo=TTF_RenderUTF8_Solid(f, cstring.c_str(), { 0,0,0,0 });
	SDL_Texture* bar = SDL_CreateTextureFromSurface(r, foo);
	SDL_FreeSurface(foo);
	TTF_CloseFont(f);
	TTF_Quit();
	return bar;
}
inline void DrawText(const char* text, SDL_Texture* font,const SDL_Rect body,SDL_Renderer* renderer)
{
	int w, h;
	std::string st = text;
	SDL_QueryTexture(font, NULL, NULL, &w, &h);
	for (int i = 0; i < st.size(); i++)
	{
		float k{(float)w/94.f};
		const SDL_Rect src{k*(st.at(i)-32),0,k,h};
		const SDL_FRect dst{body.x+ i*body.w/st.size(),body.y,body.w /st.size(),body.h};
		SDL_RenderCopyF(renderer,font,&src,&dst);
	}
}
inline void DrawTextCD(const char* text, SDL_Texture* font, const int x, const int y, const int pk, SDL_Renderer* renderer)
{
	int w, h;
	std::string st = text;
	SDL_QueryTexture(font, NULL, NULL, &w, &h);
	for (int i = 0; i < st.size(); i++)
	{
		float k{ (float)w / 94.f };
		const SDL_Rect src{ k * (st.at(i) - 32),0,k,h };
		const SDL_FRect dst{ x + i * pk,y,pk,pk * 2 };
		SDL_RenderCopyF(renderer, font, &src, &dst);
	}
}
class Label {
public: 
	Label(SDL_Texture* font,SDL_Renderer* renderer,const SDL_Rect body);
	void Draw(const char* text);
	void DrawCD(const char* text, const int pk);
	inline int GetX();
	inline int GetY();
	inline void SetX(const int x);
	inline void SetY(const int y);
private:
	SDL_Texture* font{nullptr};
	SDL_Renderer* renderer{ nullptr };
	int th=0, tw=0;
	SDL_Rect body{ NULL };
};
inline Label::Label(SDL_Texture* font, SDL_Renderer* renderer, const SDL_Rect body)
{
	this->body = body; this->font = font; this->renderer = renderer;
	SDL_QueryTexture(this->font, NULL, NULL, &tw, &th);
}
inline void Label::Draw(const char* text)
{
	std::string st = text;
	for (int i = 0; i < st.size(); i++)
	{
		float k{ (float)tw / 94.f };
		const SDL_Rect src{ k * (st.at(i) - 32),0,k,th };
		const SDL_FRect dst{ body.x + i * body.w / st.size(),body.y,body.w / st.size(),body.h };
		SDL_RenderCopyF(renderer, font, &src, &dst);
	}
}
inline void Label::SetX(const int x) { body.x = x; }
inline void Label::SetY(const int y) { body.y = y; }
inline int Label::GetX() { return body.x; }
inline int Label::GetY() { return body.y; }
inline void Label::DrawCD(const char* text, const int pk)
{
	std::string st = text;
	for (int i = 0; i < st.size(); i++)
	{
		if (i * pk < body.w)
		{
			float k{ (float)tw / 94.f };
			const SDL_Rect src{ k * (st.at(i) - 32),0,k,th };
			const SDL_FRect dst{ body.x + i * pk,body.y,pk,pk * 2 };
			SDL_RenderCopyF(renderer, font, &src, &dst);
		}
		
	}
}
#endif