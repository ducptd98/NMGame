#pragma once
#include "Enemy.h"

class Raven : public Enemy
{
public:
	GameTimeLoop* timeStopMove;
	GameTimeLoop* timeDelayMove;
	bool isMove;
	bool isDelay;
	bool isExist;
	bool isBegin;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void restore(BaseObject* obj);

	Raven();
	~Raven();
};

