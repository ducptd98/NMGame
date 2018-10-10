#pragma once
#include "Enemy.h"

class Medusa : public Enemy
{
public:
	static bool isDeath;
	static int lifeBoss;

	int count;
	int angle;
	GameTimeLoop* timeStopMove;
	GameTimeLoop* timeDelayMove;
	GameTimeLoop* timeDamaged;
	GameTimeLoop* timeEffect;
	bool isMove;
	bool isDelay;
	bool isExit;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void restore(BaseObject * obj);

	Medusa();
	~Medusa();
};

