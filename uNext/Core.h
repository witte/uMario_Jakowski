#pragma once

#ifndef CORE_H
#define CORE_H

#include "Map.h"

class CCore
{
private:
	SDL_Window* window;
	SDL_Renderer* rR;
	SDL_Event* mainEvent;
	SDL_Joystick* joystick = nullptr;

	// ----- FPS -----

	static const int MIN_FRAME_TIME = 16;

	int iNumOfFPS, iFPS;

	// ----- FPS -----

	// ----- INPUT
	static bool movePressed, keyMenuPressed, keyS, keyW, keyA, keyD, keyShift;

	static bool keyAPressed, keyDPressed;
	// ----- true = RIGHT, false = LEFT
	bool firstDir;

	// ----- INPUT

	static Map* oMap;

	// ----- Methods

	void Input();
	void MouseInput();
	void InputPlayer();
	void InputMenu();

    void joystickAdded(int deviceIndex);


public:
	CCore();
	~CCore();

	static bool quitGame;

	void mainLoop();

	void Update();
	void Draw();

	void resetMove();
	static void resetKeys();

	static bool mouseLeftPressed, mouseRightPressed;
	static float mouseX, mouseY;
	
	/* ----- get & set ----- */
	static Map* getMap();
};

#endif
