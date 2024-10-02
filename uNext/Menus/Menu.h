#pragma once

#ifndef MENU_H
#define MENU_h

#include "header.h"
#include "MenuOption.h"
#include <vector>

class Menu
{
public:
	Menu();
	~Menu();

	std::vector<MenuOption*> lMO; 

	// ----- ID aktywnego buttona
	int activeMenuOption;
	int numOfMenuOptions;

	virtual void Update();
	virtual void Draw(SDL_Renderer* rR);

	// ----- 0 = TOP, 1 = RIGHT, 2 = BOTTOM, 3 = LEFT
	virtual void updateActiveButton(int iDir);
};

#endif