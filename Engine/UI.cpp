#include "UI.h"

UI::UI()
{
}

UI::UI(Setup* setup)
{
	this->setup = setup;
	Renderer = setup->GetRenderer();
	Event = setup->GetEvent();
}

UI::UI(Setup* setup, const char* xml_path, TextureMapping* texmap)
{
	this->setup = setup;
	Renderer = setup->GetRenderer();
	Event = setup->GetEvent();
	TexMap = texmap;
}

UI::~UI()
{
}

bool UI::Events(const fvec2d& camera )
{
	const vec2d cameraI = ConvertToVec2d(camera);
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	mouseTile = {TILE_WIDTH*((mousePos.x+cameraI.x)/ TILE_WIDTH)-cameraI.x,TILE_WIDTH *((mousePos.y+ cameraI.y)/ TILE_WIDTH)- cameraI.y,TILE_WIDTH,TILE_WIDTH };

	if (Event->type == SDL_QUIT)return false;

	if (Event->type == SDL_KEYDOWN)
	{
		switch (Event->key.keysym.sym)
		{
		case SDLK_ESCAPE: return false; break;
		}
	}
	if (Event->type == SDL_MOUSEBUTTONDOWN)
	{
		switch (Event->button.button)
		{
		case SDL_BUTTON_LEFT: LEFT_CLICK = true; setup->SetCursorClick(); break;
		}
	}
	if (LEFT_UP)LEFT_UP = false;
	if (Event->type == SDL_MOUSEBUTTONUP)
	{
		switch (Event->button.button)
		{
		case SDL_BUTTON_LEFT: LEFT_UP = LEFT_CLICK; LEFT_CLICK = false; setup->SetCursorDefault();  break;
		}
	}
	return true;
}

void UI::Draw()
{
	SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer,&mouseTile);
}
