#ifndef TEXTUREMAPPING_H_
#define TEXTUREMAPPING_H_
#include <map>
#include <SDL.h>
#include "exception_handling.h"
class TextureMapping
{
public:
	TextureMapping(SDL_Renderer* renderer);
	TextureMapping(const std::map<std::string, SDL_Texture*>& v, SDL_Renderer* renderer);
	~TextureMapping();
	void Add(const char* path, const char* name);
	void Erase(const char* name);
	SDL_Texture* At(const char* name);
	SDL_Texture* At(const unsigned int id);
	void EraseAll();
private:
	std::map<std::string, SDL_Texture*> v;
	SDL_Renderer* renderer;
};

#endif