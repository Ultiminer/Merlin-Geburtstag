#include "TextureMapping.h"

TextureMapping::TextureMapping(SDL_Renderer* renderer) { this->renderer = renderer; }
TextureMapping::TextureMapping(const std::map<std::string, SDL_Texture*>& v, SDL_Renderer* renderer) { this->v = v; this->renderer = renderer; }
TextureMapping::~TextureMapping() { auto iter = v.begin(); while (iter != v.end()) { SDL_DestroyTexture(iter->second); mge::cout << "TextureMap::Erased: " << iter->first.c_str() << " obj." << mge::endl; ++iter; }  v.erase(v.begin(),v.end()); }
void TextureMapping::Add(const char* path, const char* name) { SDL_Surface* temp{ SDL_LoadBMP(path) }; const Uint32 color_key = SDL_MapRGB(temp->format, 255, 255, 255); SDL_SetColorKey(temp, 1, color_key); v.insert({ name,SDL_CreateTextureFromSurface(renderer,temp) }); SDL_FreeSurface(temp); temp = NULL; mge::cout << "Added: " << name << " texture!!" << mge::endl; }
void TextureMapping::Erase(const char* name)
{
	v.erase(name);
}
SDL_Texture* TextureMapping::At(const char* name)
{
	return v.at(name);
}

SDL_Texture* TextureMapping::At(const unsigned int id)
{
	auto iter = v.begin();
	for(int i=0; i<id;i++)++iter;
	
	return iter->second;
}

void TextureMapping::EraseAll() { v.erase(v.begin(), v.end()); }