#pragma once

#ifndef IMG_H
#define IMG_H

#include "header.h"

class CIMG
{
private:
	SDL_Texture* tIMG;
	SDL_FRect rRect;

public:
	CIMG();
	CIMG(std::string fileName, SDL_Renderer* rR);
	~CIMG();

	void Draw(SDL_Renderer * rR, int iXOffset, int iYOffset);
	void Draw(SDL_Renderer * rR, int iXOffset, int iYOffset, bool bRoate);
	void DrawVert(SDL_Renderer * rR, int iXOffset, int iYOffset);
	void Draw(SDL_Renderer * rR, SDL_FRect rCrop, SDL_FRect rRect);

	/* ----- get & set ----- */
	SDL_Texture* getIMG();
	void setIMG(std::string fileName, SDL_Renderer* rR);
	SDL_FRect getRect();
};

#endif