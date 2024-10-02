#pragma once

#ifndef CHEEPSPAWNER_H
#define CHEEPSPAWNER_H

#include "Entities/Minion.h"

class CheepSpawner : public Minion
{
private:
	int iXEnd;

	unsigned int iSpawnTime;
public:
	CheepSpawner(int iXPos, int iXEnd);
	~CheepSpawner();

	void Update();
	void minionPhysics();

	void spawnCheep();
	void nextCheep();
};

#endif