#pragma once

#ifndef BULLETBILLSPAWNER_H
#define BULLETBULLSPAWNER_H

#include "Entities/Minion.h"

class BulletBillSpawner : public Minion
{
private:
	int nextBulletBillFrameID;
public:
	BulletBillSpawner(int iXPos, int iYPos, int minionState);
	~BulletBillSpawner();

	void Update();

	void minionPhysics();
};

#endif