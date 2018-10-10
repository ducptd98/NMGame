#pragma once
#include "Enemy.h"

class BoneTower : public Enemy
{
public:
	GameTimeLoop* gameTimeLoopBullet;
	GameTimeLoop* timeChangeColor;

	int countBullet = 0;
	bool isChangeColor;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject* obj);

	BoneTower();
	~BoneTower();
};

