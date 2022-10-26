#pragma once
#include "Setup.h"
#include "UI_Elements.h"
#include "texturemapping.h"
#include "Camera.h"
class UI
{
public:
	UI();
	UI(Setup* setup);
	UI(Setup* setup, const char* xml_path, TextureMapping* texmap);
	~UI();
	bool Events(const fvec2d& camera = { 0,0 });
	void Draw();
private:
	Setup* setup=nullptr;
	SDL_Event* Event = nullptr;
	SDL_Renderer* Renderer = nullptr;
	TextureMapping* TexMap = nullptr;
	bool LEFT_CLICK = false, LEFT_UP = false;
	SDL_Rect mouseTile = {0};
	SDL_Point mousePos = { 0 };
};

