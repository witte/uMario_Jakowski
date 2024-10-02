/************************
 * @author �ukasz Jakowski
 * @since  02.05.2014 16:13
 * 
 ************************/

#include "MusicManager.h"

/* ******************************************** */

MusicManager::MusicManager(void) {
	

	
}

MusicManager::~MusicManager(void) {

}

/* ******************************************** */

void MusicManager::PlayMusic() {
    const std::string basePath = SDL_GetBasePath();

    vMusic.push_back(Mix_LoadMUS((basePath + "files/sounds/overworld.wav").c_str()));
    vMusic.push_back(Mix_LoadMUS((basePath + "files/sounds/overworld.wav").c_str()));
	Mix_VolumeMusic(100);
	Mix_OpenAudio(0, nullptr);
	Mix_PlayMusic(vMusic[0], -1);
}

/* ******************************************** */

Mix_Music* MusicManager::loadMusic(std::string fileName) {
    const std::string basePath = SDL_GetBasePath();

    fileName = basePath + "files/sounds/" + fileName + ".wav";
    const std::string hardCodedWrongPath = basePath + "files/sounds/overworld.wav";

    return Mix_LoadMUS(hardCodedWrongPath.c_str());
}

/* ******************************************** */