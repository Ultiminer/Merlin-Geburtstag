#pragma once
#include "UI.h"
#include <iostream>
#include "Character.h"
#include "exception_handling.h"
#include "camera.h"
#include "engineFileFormat.h"
#include "Enemies.h"
#include "textbox.h"


class Application
{
public:
	Application();
	~Application();
	void Gameloop();
private:
	void Gfx();
	void Events();
	void UIEvents();
	void Physics();

	Setup* setup;
	SDL_Event* Event;
	UI Ui;
	Character character;

	TextureMapping* map=nullptr;
	Healthbar healthbar;

	Uint32 dtime = 0,starttime = 0,delay=0;
	
	bool running=true;

	
	Sprite heart;

	SDL_Point* WindowSize = nullptr;
	
	Camera cam;

	Sprite mouth;
};