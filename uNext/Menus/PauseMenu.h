#pragma once

#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Menu.h"

class PauseMenu : public Menu
{
private:
	SDL_FRect rPause;
public:
	PauseMenu();
	~PauseMenu();

	void Update();
	void Draw(SDL_Renderer* rR);

	void enter();
	void escape();

	void updateActiveButton(int iDir);
};

#endif