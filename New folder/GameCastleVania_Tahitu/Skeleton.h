#pragma once
#include "Enemy.h"

class Skeleton : public Enemy
{
public:
	GameTimeLoop* timeCreateBone;
	int count;
	bool isChangeMoving;
	bool isJumping;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject* obj);

	Skeleton();
	~Skeleton();
};
