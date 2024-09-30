#include "Core.h"
#if defined(__IPHONEOS__) || defined(__TVOS__)

/*
    SDL_uikit_main.c, placed in the public domain by Sam Lantinga  3/18/2019
*/

/* Include the SDL main definition header */


#ifndef SDL_MAIN_HANDLED
#ifdef main
#undef main
#endif


int SDL_main(int argc, char *argv[])
{
    CCore oCore;

    oCore.mainLoop();

    return 0;
}

int main(int argc, char *argv[])
{
    return SDL_UIKitRunApp(argc, argv, SDL_main);
}
#endif /* !SDL_MAIN_HANDLED */

#else

int main(int argc, char *argv[])
{
	CCore oCore;
	
	oCore.mainLoop();

	return 0;
}

#endif /* __IPHONEOS__ || __TVOS__ */
