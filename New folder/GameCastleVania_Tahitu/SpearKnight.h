#pragma once
#include "Enemy.h"

class SpearKnight : public Enemy
{
public:
	bool changeDirection;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject* obj);

	SpearKnight();
	~SpearKnight();
};

