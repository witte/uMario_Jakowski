#include <iostream>
#include "header.h"
#include "Core.h"
#include "IMG.h"
#include "CFG.h"
#include "Text.h"
#include "SDL_mixer.h"

/* ******************************************** */

Map* CCore::oMap = new Map();
bool CCore::mouseLeftPressed = false;
bool CCore::mouseRightPressed = false;
int CCore::mouseX = 0;
int CCore::mouseY = 0;
bool CCore::quitGame = false;

bool CCore::movePressed = false;
bool CCore::keyMenuPressed = false;
bool CCore::keyS = false;
bool CCore::keyW = false;
bool CCore::keyA = false;
bool CCore::keyD = false;
bool CCore::keyShift = false;
bool CCore::keyAPressed = false;
bool CCore::keyDPressed = false;


enum class DualSenseButtons {
#if defined(__IPHONEOS__) || defined(__TVOS__)
    DPAD_LEFT = 8,
    DPAD_UP = 10,
    DPAD_RIGHT = 9,
    DPAD_DOWN = 7,
    X = 5,
    SQUARE = 0,
    CIRCLE = 1,
    TRIANGLE = 6,
    RIGHTSHOULDER = 14,
    PAUSE = 3,
#else
    DPAD_LEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
    DPAD_UP = SDL_CONTROLLER_BUTTON_DPAD_UP,
    DPAD_RIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
    DPAD_DOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
    X = SDL_CONTROLLER_BUTTON_A,
    SQUARE = SDL_CONTROLLER_BUTTON_X,
    CIRCLE = SDL_CONTROLLER_BUTTON_B,
    TRIANGLE = SDL_CONTROLLER_BUTTON_Y,
    RIGHTSHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
    PAUSE = SDL_CONTROLLER_BUTTON_START,
#endif
};


CCore::CCore(void) {
	this->quitGame = false;
	this->iFPS = 0;
	this->iNumOfFPS = 0;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);
	
	window = SDL_CreateWindow("uMario - www.LukaszJakowski.pl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CCFG::GAME_WIDTH, CCFG::GAME_HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL) {
		quitGame = true;
	}

	if (SDL_NumJoysticks() >= 1) {
		joystick = SDL_JoystickOpen(0);
		if (joystick == nullptr) {
			std::cerr << "Could not open joystick! SDL Error: " << SDL_GetError() << std::endl;
		}

		std::cout << "Joystick connected: " << SDL_JoystickName(joystick) << std::endl;
		std::cout << "Number of buttons: " << SDL_JoystickNumButtons(joystick) << std::endl;
	}

	rR = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// ----- ICO
    std::string fileName = SDL_GetBasePath();
    fileName += "files/images/ico.bmp";
	SDL_Surface* loadedSurface = SDL_LoadBMP(fileName.c_str());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

	SDL_SetWindowIcon(window, loadedSurface);
	SDL_FreeSurface(loadedSurface);

	mainEvent = new SDL_Event();
	// ----- ICO
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
	oMap = new Map(rR);
	CCFG::getMM()->setActiveOption(rR);
	CCFG::getSMBLOGO()->setIMG("super_mario_bros", rR);

	CCFG::getMusic()->PlayMusic();

	this->keyMenuPressed = this->movePressed = this->keyS = this->keyW = this->keyA = this->keyD = this->keyShift = false;

	this->keyAPressed = this->keyDPressed = this->firstDir = false;

	this->mouseX = this->mouseY = 0;

	CCFG::keyIDA = SDLK_a;
	CCFG::keyIDS = SDLK_s;
	CCFG::keyIDD = SDLK_d;
	CCFG::keyIDSpace = SDLK_SPACE;
	CCFG::keyIDShift = SDLK_LSHIFT;
}

CCore::~CCore(void) {
	delete oMap;
	delete mainEvent;
	SDL_DestroyRenderer(rR);
	SDL_DestroyWindow(window);
	SDL_JoystickClose(joystick);
	SDL_Quit();

	joystick = nullptr;
	window = nullptr;
}

/* ******************************************** */

void CCore::mainLoop()
{
	auto nextFrameTime = SDL_GetTicks() + MIN_FRAME_TIME;
	auto frameTime = SDL_GetTicks();

	while (!quitGame && mainEvent->type != SDL_QUIT) {
        if (mainEvent->type == SDL_JOYDEVICEADDED)
        {
            joystickAdded(mainEvent->jdevice.which);
        }
		// TODO: handle joystick removal
        // else if (mainEvent->type == SDL_JOYDEVICEREMOVED)
        // {
        //     joystickAdded(mainEvent->jdevice.which);
        // }

		SDL_PollEvent(mainEvent);
		Input();

		const auto currentFrameTime = SDL_GetTicks();
		if (SDL_GetTicks() > nextFrameTime)
		{
			nextFrameTime = currentFrameTime + MIN_FRAME_TIME;

			Update();
			CCFG::getMM()->setBackgroundColor(rR);
			SDL_RenderClear(rR);

			Draw();
			SDL_RenderPresent(rR);
		}
	}
}

void CCore::Input() {
	switch(CCFG::getMM()->getViewID()) {
		case 2: case 7:
			if(!oMap->getInEvent()) {
				InputPlayer();
			} else {
				resetMove();
			}
			break;
		default:
			InputMenu();
			break;
	}
}

void CCore::InputMenu() {
	if (mainEvent->type == SDL_JOYBUTTONDOWN) {
        switch (static_cast<DualSenseButtons>(mainEvent->jbutton.button)) {
            case DualSenseButtons::DPAD_LEFT:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(3);
					keyMenuPressed = true;
				}
				break;
            case DualSenseButtons::DPAD_UP:
				if (!keyMenuPressed) {
					CCFG::getMM()->keyPressed(0);
					keyMenuPressed = true;
				}
				break;
            case DualSenseButtons::DPAD_DOWN:
				if (!keyMenuPressed) {
					CCFG::getMM()->keyPressed(2);
					keyMenuPressed = true;
				}
				break;
            case DualSenseButtons::DPAD_RIGHT:
				if (!keyMenuPressed) {
					CCFG::getMM()->keyPressed(1);
					keyMenuPressed = true;
				}
				break;
            case DualSenseButtons::X:
            case DualSenseButtons::SQUARE:
				if (!keyMenuPressed) {
					CCFG::getMM()->enter();
					keyMenuPressed = true;
				}
				break;
            case DualSenseButtons::CIRCLE:
            case DualSenseButtons::TRIANGLE:
            case DualSenseButtons::RIGHTSHOULDER:
				if (!keyMenuPressed) {
					CCFG::getMM()->escape();
					keyMenuPressed = true;
				}
				break;
			default:
				break;
		}
	}

	if(mainEvent->type == SDL_KEYDOWN) {
		CCFG::getMM()->setKey(mainEvent->key.keysym.sym);

		switch(mainEvent->key.keysym.sym) {
			case SDLK_s: case SDLK_DOWN:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(2);
					keyMenuPressed = true;
				}
				break;
			case SDLK_w: case SDLK_UP:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(0);
					keyMenuPressed = true;
				}
				break;
			case SDLK_KP_ENTER: case SDLK_RETURN:
				if(!keyMenuPressed) {
					CCFG::getMM()->enter();
					keyMenuPressed = true;
				}
				break;
			case SDLK_ESCAPE:
				if(!keyMenuPressed) {
					CCFG::getMM()->escape();
					keyMenuPressed = true;
				}
				break;
			case SDLK_LEFT: case SDLK_a:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(3);
					keyMenuPressed = true;
				}
				break;
			case SDLK_RIGHT: case SDLK_d:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(1);
					keyMenuPressed = true;
				}
				break;
		}
	}

	else if (mainEvent->type == SDL_JOYBUTTONUP) {
		keyMenuPressed = false;
	}

	if(mainEvent->type == SDL_KEYUP) {
		switch(mainEvent->key.keysym.sym) {
			case SDLK_s:
			case SDLK_DOWN:
			case SDLK_w:
			case SDLK_UP:
			case SDLK_KP_ENTER:
			case SDLK_RETURN:
			case SDLK_ESCAPE:
			case SDLK_a:
			case SDLK_RIGHT:
			case SDLK_LEFT:
			case SDLK_d:
				keyMenuPressed = false;
				break;
			default:
				break;
		}
	}
}

void CCore::joystickAdded(int deviceIndex) {
    SDL_Joystick* newJoystick = SDL_JoystickOpen(deviceIndex);

    if (newJoystick) {
        joystick = newJoystick;
    } else {
        std::cerr << "Failed to open joystick: " << SDL_GetError() << std::endl;
    }
}

void CCore::InputPlayer() {
	if(mainEvent->type == SDL_WINDOWEVENT) {
		switch(mainEvent->window.event) {
			case SDL_WINDOWEVENT_FOCUS_LOST:
				CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->ePasue);
				CCFG::getMM()->setViewID(CCFG::getMM()->ePasue);
				CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cPASUE);
				CCFG::getMusic()->PauseMusic();
				break;
		}
	}

	else if (mainEvent->type == SDL_JOYBUTTONDOWN) {
        switch (static_cast<DualSenseButtons>(mainEvent->jbutton.button)) {
            case DualSenseButtons::DPAD_LEFT:
				keyAPressed = true;
				if (!keyDPressed)
					firstDir = false;

				break;
            case DualSenseButtons::DPAD_DOWN:
				keyS = true;
				if(!oMap->getUnderWater() && !oMap->getPlayer()->getInLevelAnimation())
					oMap->getPlayer()->setSquat(true);

				break;
            case DualSenseButtons::DPAD_RIGHT:
				keyDPressed = true;
				if (!keyAPressed)
					firstDir = true;

				break;
            case DualSenseButtons::X:
            case DualSenseButtons::SQUARE:
				if (!CCFG::keySpace) {
					oMap->getPlayer()->jump();
					CCFG::keySpace = true;
				}
				break;
            case DualSenseButtons::CIRCLE:
            case DualSenseButtons::TRIANGLE:
            case DualSenseButtons::RIGHTSHOULDER:
				if (!keyShift) {
					oMap->getPlayer()->startRun();
					keyShift = true;
				}
				break;
			// TODO: figure out x/circle handling on menu
            // case SDLK_KP_ENTER: case SDLK_RETURN:
            //     if (!keyMenuPressed) {
            //         CCFG::getMM()->enter();
            //         keyMenuPressed = true;
            //     }
            //     break;
            case DualSenseButtons::PAUSE:
                if (!keyMenuPressed && CCFG::getMM()->getViewID() == CCFG::getMM()->eGame) {
                    CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->ePasue);
                    CCFG::getMM()->setViewID(CCFG::getMM()->ePasue);
                    CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cPASUE);
                    CCFG::getMusic()->PauseMusic();
                    keyMenuPressed = true;
                }
			default:
				break;
		}
	}
	else if (mainEvent->type == SDL_JOYBUTTONUP) {
        switch (static_cast<DualSenseButtons>(mainEvent->jbutton.button)) {
            case DualSenseButtons::DPAD_LEFT: // left
				keyAPressed = false;

				break;
            case DualSenseButtons::DPAD_DOWN: // down
				keyS = false;
				oMap->getPlayer()->setSquat(false);

				break;
            case DualSenseButtons::DPAD_RIGHT: // right
				keyDPressed = false;
				if (firstDir)
					firstDir = false;

				break;
            case DualSenseButtons::X:
            case DualSenseButtons::SQUARE: // jump
				CCFG::keySpace = false;

				break;
            case DualSenseButtons::CIRCLE:
            case DualSenseButtons::TRIANGLE:
            case DualSenseButtons::RIGHTSHOULDER: // run / throw fireball
				if (keyShift) {
					oMap->getPlayer()->resetRun();
					keyShift = false;
				}

				break;
            case DualSenseButtons::PAUSE:
                keyMenuPressed = false;
                break;
			default:
				break;
		}
	}

	if(mainEvent->type == SDL_KEYUP) {
		if(mainEvent->key.keysym.sym == CCFG::keyIDD) {
				if(firstDir) {
					firstDir = false;
				}

				keyDPressed = false;
			}

			if(mainEvent->key.keysym.sym == CCFG::keyIDS) {
				oMap->getPlayer()->setSquat(false);
				keyS = false;
			}
		
			if(mainEvent->key.keysym.sym == CCFG::keyIDA) {
				if(!firstDir) {
					firstDir = true;
				}

				keyAPressed = false;
			}
		
			if(mainEvent->key.keysym.sym == CCFG::keyIDSpace) {
				CCFG::keySpace = false;
			}
		
			if(mainEvent->key.keysym.sym == CCFG::keyIDShift) {
				if(keyShift) {
					oMap->getPlayer()->resetRun();
					keyShift = false;
				}
			}
		switch(mainEvent->key.keysym.sym) {
			case SDLK_KP_ENTER: case SDLK_RETURN: case SDLK_ESCAPE:
				keyMenuPressed = false;
				break;
		}
	}

	if(mainEvent->type == SDL_KEYDOWN) {
		if(mainEvent->key.keysym.sym == CCFG::keyIDD) {
			keyDPressed = true;
			if(!keyAPressed) {
				firstDir = true;
			}
		}

        if(mainEvent->key.keysym.sym == CCFG::keyIDS) {
			if(!keyS) {
				keyS = true;
				if(!oMap->getUnderWater() && !oMap->getPlayer()->getInLevelAnimation()) oMap->getPlayer()->setSquat(true);
			}
		}
		
        if(mainEvent->key.keysym.sym == CCFG::keyIDA) {
			keyAPressed = true;
			if(!keyDPressed) {
				firstDir = false;
			}
		}
		
        if(mainEvent->key.keysym.sym == CCFG::keyIDSpace) {
			if(!CCFG::keySpace) {
				oMap->getPlayer()->jump();
				CCFG::keySpace = true;
			}
		}
		
        if(mainEvent->key.keysym.sym == CCFG::keyIDShift) {
			if(!keyShift) {
				oMap->getPlayer()->startRun();
				keyShift = true;
			}
		}

		switch(mainEvent->key.keysym.sym) {
			case SDLK_KP_ENTER: case SDLK_RETURN:
				if(!keyMenuPressed) {
					CCFG::getMM()->enter();
					keyMenuPressed = true;
				}
                break;
			case SDLK_ESCAPE:
				if(!keyMenuPressed && CCFG::getMM()->getViewID() == CCFG::getMM()->eGame) {
					CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->ePasue);
					CCFG::getMM()->setViewID(CCFG::getMM()->ePasue);
					CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cPASUE);
					CCFG::getMusic()->PauseMusic();
					keyMenuPressed = true;
				}
				break;
		}
	}

	if(keyAPressed) {
		if(!oMap->getPlayer()->getMove() && firstDir == false && !oMap->getPlayer()->getChangeMoveDirection() && !oMap->getPlayer()->getSquat()) {
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection(false);
		} else if(!keyDPressed && oMap->getPlayer()->getMoveSpeed() > 0 && firstDir != oMap->getPlayer()->getMoveDirection()) {
			oMap->getPlayer()->setChangeMoveDirection();
		}
	}

	if(keyDPressed) {
		if(!oMap->getPlayer()->getMove() && firstDir == true && !oMap->getPlayer()->getChangeMoveDirection() && !oMap->getPlayer()->getSquat()) {
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection(true);
		} else if(!keyAPressed && oMap->getPlayer()->getMoveSpeed() > 0 && firstDir != oMap->getPlayer()->getMoveDirection()) {
			oMap->getPlayer()->setChangeMoveDirection();
		}
	}

	if(oMap->getPlayer()->getMove() && !keyAPressed && !keyDPressed) {
		oMap->getPlayer()->resetMove();
	}
}

void CCore::MouseInput() {
	switch(mainEvent->type) {
		case SDL_MOUSEBUTTONDOWN: {
			switch (mainEvent->button.button) {
				case SDL_BUTTON_LEFT:
					mouseLeftPressed = true;
					break;
				case SDL_BUTTON_RIGHT:
					mouseRightPressed = true;
					break;
			}
			break;
		}
		case SDL_MOUSEMOTION: {
			
			SDL_GetMouseState(&mouseX, &mouseY);
			//CCFG::getMM()->getConsole()->print("x:" + std::to_string(mouseX));
			//CCFG::getMM()->getConsole()->print("y:" + std::to_string(mouseY));
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			switch (mainEvent->button.button) {
				case SDL_BUTTON_LEFT:
					mouseLeftPressed = false;
					break;
				case SDL_BUTTON_RIGHT:
					mouseRightPressed = false;
					break;
			}
			break;
		}
		case SDL_MOUSEWHEEL:
			if(mainEvent->wheel.timestamp > SDL_GetTicks() - 2) {
				//CCFG::getMM()->getLE()->mouseWheel(mainEvent->wheel.y);
			}
			break;
	}
}

void CCore::resetKeys() {
	movePressed = keyMenuPressed = keyS = keyW = keyA = keyD = CCFG::keySpace = keyShift = keyAPressed = keyDPressed = false;
}

void CCore::Update() {
	CCFG::getMM()->Update();
}


void CCore::Draw() {
	CCFG::getMM()->Draw(rR);
}

/* ******************************************** */

void CCore::resetMove() {
	this->keyAPressed = this->keyDPressed = false;
}

Map* CCore::getMap() {
	return oMap;
}
