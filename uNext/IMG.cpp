#include "IMG.h"

/* ******************************************** */

CIMG::CIMG() { }

CIMG::CIMG(std::string fileName, SDL_Renderer* rR) {
	setIMG(fileName, rR);
}

CIMG::~CIMG() {
	SDL_DestroyTexture(tIMG);
}

/* ******************************************** */

void CIMG::Draw(SDL_Renderer* rR, int iXOffset, int iYOffset) {
	rRect.x = iXOffset;
	rRect.y = iYOffset;

	SDL_RenderTexture(rR, tIMG, NULL, &rRect);
}

void CIMG::Draw(SDL_Renderer* rR, int iXOffset, int iYOffset, bool bRotate) {
	rRect.x = iXOffset;
	rRect.y = iYOffset;

	if(!bRotate) {
		SDL_RenderTexture(rR, tIMG, NULL, &rRect);
	} else {
		SDL_RenderTextureRotated(rR, tIMG, NULL, &rRect, 180.0, NULL, SDL_FLIP_VERTICAL);
	}
}

void CIMG::DrawVert(SDL_Renderer* rR, int iXOffset, int iYOffset) {
	rRect.x = iXOffset;
	rRect.y = iYOffset;

	SDL_RenderTextureRotated(rR, tIMG, NULL, &rRect, 180.0, NULL, SDL_FLIP_HORIZONTAL);
}

void CIMG::Draw(SDL_Renderer* rR, SDL_FRect rCrop, SDL_FRect rRect) {
	SDL_RenderTexture(rR, tIMG, &rCrop, &rRect);
}

/* ******************************************** */

void CIMG::setIMG(std::string fileName, SDL_Renderer* rR) {
    const std::string basePath = SDL_GetBasePath();
    fileName = basePath + "files/images/" + fileName + ".bmp";
	SDL_Surface* loadedSurface = SDL_LoadBMP(fileName.c_str());

	// SDL_PixelFormatDetails formatDetails = loadedSurface->fmt;

	const auto rgbMap = SDL_MapSurfaceRGB(loadedSurface, 255, 0, 255);
	SDL_SetSurfaceColorKey(loadedSurface, true, rgbMap);
	// SDL_SetSurfaceColorKey(loadedSurface, true, 0xff00ff);

	tIMG = SDL_CreateTextureFromSurface(rR, loadedSurface);
	float iWidth, iHeight;

	// SDL_QueryTexture(tIMG, NULL, NULL, &iWidth, &iHeight);
	SDL_GetTextureSize(tIMG, &iWidth, &iHeight);
	
	rRect.x  = 0;
	rRect.y = 0;
	rRect.w = iWidth;
	rRect.h = iHeight;
	SDL_DestroySurface(loadedSurface);
}

SDL_Texture* CIMG::getIMG() {
	return tIMG;
}

SDL_FRect CIMG::getRect() {
	return rRect;
}