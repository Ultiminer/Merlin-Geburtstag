#include "Setup.h"

Setup::Setup()
{

	std::string title = XMLValue(SETUPSETTINGSFILENAME, "WINDOW_NAME");
	fps = atoi(XMLValue(SETUPSETTINGSFILENAME, "FRAMERATE").c_str());
	std::string icon_path= XMLValue(SETUPSETTINGSFILENAME, "GAME_ICON");
	std::string cursor_path= XMLValue(SETUPSETTINGSFILENAME, "CURSOR_ICON");
	std::string cursor_click_path = XMLValue(SETUPSETTINGSFILENAME, "CURSOR_CLICK_ICON");

	bool ms= atoi(XMLValue(SETUPSETTINGSFILENAME, "MOUSE_SHOWN").c_str());
	SDL_Init(SDL_INIT_VIDEO);


	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	screen = {DM.w,DM.h};

	Window = SDL_CreateWindow(title.c_str(), 0,25, screen.x, screen.y - 20,SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_INPUT_FOCUS|SDL_WINDOW_MOUSE_FOCUS);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	Event = new SDL_Event();

	iconSurface = SDL_LoadBMP(icon_path.c_str());
	SDL_SetWindowIcon(Window, iconSurface);

	cursorSurface = SDL_LoadBMP(cursor_path.c_str());
	uint32_t color_key = SDL_MapRGB(cursorSurface->format, 255, 255, 255);
	SDL_SetColorKey(cursorSurface, 1,color_key);
	cursor = SDL_CreateColorCursor(cursorSurface, 0,0);
	SDL_SetCursor(cursor);

	cursorClickSurface = SDL_LoadBMP(cursor_click_path.c_str());
	color_key = SDL_MapRGB(cursorClickSurface->format, 255, 255, 255);
	SDL_SetColorKey(cursorClickSurface, 1, color_key);

	cursor_click = SDL_CreateColorCursor(cursorClickSurface, 0, 0);

	SDL_GetWindowSize(Window, &window_size.x, &window_size.y);
	SDL_ShowCursor(ms);

	MGE_PRINT("ALLOCATING MGE_TEXTBOX FROM SETUP CLASS");
	mge::textbox = new MGE_STD_TEXTBOX(Renderer);
}

Setup::~Setup()
{
	MGE_PRINT("Freeing cursor!");
	SDL_FreeCursor(cursor);
	MGE_PRINT("Freeing cursor click!");
	SDL_FreeCursor(cursor_click);
	MGE_PRINT("Destroying window!");
	SDL_DestroyWindow(Window);
	MGE_PRINT("Destroying renderer!");
	SDL_DestroyRenderer(Renderer);
	MGE_PRINT("Freeing iconSurface!");
	SDL_FreeSurface(iconSurface);
	MGE_PRINT("Freeing cursorSurface!");
	SDL_FreeSurface(cursorSurface);
	MGE_PRINT("Freeing cursorClickSurface!");
	SDL_FreeSurface(cursorClickSurface);
	MGE_PRINT("Deleting event!");
	delete Event;
	MGE_PRINT("Calling SDL_Quit()!");
	SDL_Quit();
	MGE_PRINT("DELETING MGE TEXTBOX");
	delete mge::textbox;
	delete mouse;
}

SDL_Window* Setup::GetWindow()
{
	return Window;
}

SDL_Renderer* Setup::GetRenderer()
{
	return Renderer;
}

SDL_Event* Setup::GetEvent()
{
	return Event;
}


int Setup::GetFPS()
{
	return fps;
}

void Setup::StartDrawing()
{
	SDL_RenderClear(Renderer);
}

void Setup::EndDrawing()
{
	mge::textbox->draw();
	SDL_RenderPresent(Renderer);
}

void Setup::PollEvent()
{
	SDL_PollEvent(Event);
	SDL_GetMouseState(&mouse->x,&mouse->y);
	mouse->down = (Event->type==SDL_MOUSEBUTTONDOWN);
	mouse->up = (Event->type == SDL_MOUSEBUTTONUP);
	mouse->button = Event->button.button;
}

SDL_Point* Setup::GetWindowSize()
{
	return &window_size;
}



void Setup::SetRenderDrawColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, a);
}

void Setup::SetRenderDrawColor(const unsigned char r, const unsigned char g, const unsigned char b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b,255);
}

void Setup::SetCursorDefault()
{
	SDL_SetCursor(cursor);
}

void Setup::SetCursorClick()
{
	SDL_SetCursor(cursor_click);
}

SDL_Mouse* Setup::GetMouse()
{
	return mouse;
}
