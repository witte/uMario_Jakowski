#pragma once

#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H	

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <vector>

class MusicManager
{
private:
	std::vector<Mix_Music*> vMusic;

	std::vector<Mix_Chunk*> vChunk;
public:
	MusicManager(void);
	~MusicManager(void);

	Mix_Music* loadMusic(std::string fileName);

	void PlayMusic();

};

#endif