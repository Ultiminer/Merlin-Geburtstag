#include "Application.h"

Application::Application()
{
	MGE_PRINT("Created Application class!!");
	setup = new Setup();
	WindowSize = setup->GetWindowSize();
	MGE_PRINT("Initialized Setup class!!");

	Event = setup->GetEvent();
	MGE_PRINT("Set Event var in Application class!");
	map = new TextureMapping(setup->GetRenderer());
	MGE_PRINT("CREATED TEXTURE MAP");
	MGE_DOUBLE_FILL(map->Add, "../src/data/images.mge_double");
	MGE_PRINT("Filled Textures!");

	cam = Camera(ConvertToFVec2d(*WindowSize));
	MGE_PRINT("Initialized Camera!!");



	healthbar = Healthbar(setup->GetRenderer(), map->At("HEALTHBAR"), { 10,10,(float)(WindowSize->x) / 5,(float)(WindowSize->x) / 20 }, 100);
	healthbar.SetMana(75);
	healthbar.Damage();

	character = Character(setup->GetRenderer(), setup->GetEvent(), &dtime, setup->GetWindowSize()->x, map->At("MERLIN_TEST"));
	character.SetX(static_cast<float>(WindowSize->x) / 2); character.SetY(static_cast<float>(WindowSize->y) / 2);

	MGE_PRINT("Initialized Character var in Application class!");
	delay = 0;

	heart = Sprite(setup->GetRenderer(), map->At("VELO"), { 500,500,60,60 });
	heart.SetAnimation(4, 1, 4);

	mouth = Sprite(setup->GetRenderer(), map->At("MOUTH"), { 0,0,30,20 });
	mouth.SetAnimation(2,1,1);

	Ui = UI(setup, "ui_scheme.xml", map);

}

Application::~Application()
{
	delete map;
	MGE_PRINT("Deleted TEXTURE_MAP");
	delete setup;
	MGE_PRINT("Deleted setup class");
}

void Application::Gameloop()
{
	while (running)
	{
		starttime = SDL_GetTicks();
		const int m = 1000 / setup->GetFPS() - dtime;
		if (m && delay == 0)delay = SDL_GetTicks() + m;
		if (delay < SDL_GetTicks())Gfx();
		Events();
		UIEvents();
		Physics();
		MGE_CONSOLE("x: "+std::to_string(character.GetPos().x)+" y: "+std::to_string(character.GetPos().y));
		dtime = SDL_GetTicks() - starttime;
	}
}

void Application::Gfx()
{
	delay = 0;
	setup->StartDrawing();
	heart.Animate();
	heart.Draw();


	character.Animate();
	character.Draw();	

	mouth.SetPos(character.GetX() + 25, character.GetY() + 80);
	mouth.Draw();

	healthbar.Draw();
	Ui.Draw();
	SDL_SetRenderDrawColor(setup->GetRenderer(),240, 240,  240, 255);
	setup->EndDrawing();
}


void Application::Events()
{
	setup->PollEvent();
	character.UpdateEvents();
}

void Application::UIEvents()
{
	if (!Ui.Events(cam.GetPos()))running = false;
}

void Application::Physics()
{
	cam.ObjUpdate(character.GetBody(),character.GetSpeed() * dtime);
	character.SetCamera(cam.GetPos());
	heart.SetCamera(cam.GetPos());
	mouth.SetCamera(cam.GetPos());

	character.SetLowerHalf(ResRvR(character.GetLowerHalf(),heart.GetBody()));
}
