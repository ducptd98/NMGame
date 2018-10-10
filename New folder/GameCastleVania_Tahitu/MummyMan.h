#pragma once
#include "Enemy.h"

class MummyMan : public Enemy
{
public:
	static int Boss;
	static MummyMan* Boss1;
	static MummyMan* Boss2;

	int health;
	GameTimeLoop* timeStopMove;
	GameTimeLoop* timeDelayMove;
	GameTimeLoop* timeDamaged;
	GameTimeLoop* timeEffect;
	bool isMove;
	bool isDelay;
	int isDraw;
	bool isInvisible;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void restore(BaseObject * obj);

	MummyMan();
	~MummyMan();
};
