#pragma once
#include <string>
#include <SDL3/SDL.h>


class Texture
{
public:
	Texture(std::string fileName);
	~Texture();

	void Draw();
	void Draw(int offsetX, int offsetY);

	SDL_Texture* getTexture();
private:
	SDL_Texture* texture;


};

