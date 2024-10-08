#pragma once

#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"

class MainMenu : public Menu
{
private:
	bool selectWorld;
	int activeWorldID, activeSecondWorldID;

	SDL_FRect rSelectWorld;
public:
	MainMenu();
	~MainMenu();

	void Update();
	void Draw(SDL_Renderer* rR);

	void enter();
	void escape();

	void updateActiveButton(int iDir);
};

#endif