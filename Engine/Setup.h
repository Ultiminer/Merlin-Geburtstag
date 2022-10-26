#ifndef SETUP_H_
#define SETUP_H_
#include "config.h"
#include "readxml.h"
#include <SDL.h>
#include "exception_handling.h"



struct SDL_Mouse {
	int x; int y; bool up; bool down; unsigned char button;
};
class Setup
{
public:
	Setup();
	~Setup();
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	SDL_Event* GetEvent();
	int GetFPS();
	void StartDrawing();
	void EndDrawing();
	void PollEvent();
	SDL_Point* GetWindowSize();
	void SetRenderDrawColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a);
	void SetRenderDrawColor(const unsigned char r, const unsigned char g, const unsigned char b);
	void SetCursorDefault();
	void SetCursorClick();
	SDL_Mouse* GetMouse();
private:
	SDL_Window* Window=nullptr;
	SDL_Renderer* Renderer = nullptr;
	SDL_Event* Event = nullptr;
	
	SDL_Point screen;
	SDL_Point window_size;
	int fps;
	SDL_Mouse* mouse = new SDL_Mouse();
	SDL_Surface* cursorSurface = nullptr;
	SDL_Surface* cursorClickSurface = nullptr;
	SDL_Surface* iconSurface=nullptr;
	SDL_Cursor* cursor=nullptr;
	SDL_Cursor* cursor_click = nullptr;
};
#endif
