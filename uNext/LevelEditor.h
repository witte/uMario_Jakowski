#pragma once

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "header.h"

class LevelEditor
{
private:
	SDL_FRect rBlock;

	SDL_FRect rDrag;

	int currentBlockID;
public:
	LevelEditor(void);
	~LevelEditor(void);

	void Update();
	void Draw(SDL_Renderer* rR);

	void mouseWheel(int Y);
	
	void editMap();

	void drawStruct(SDL_Renderer* rR);
};

#endif