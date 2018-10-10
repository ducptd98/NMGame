#pragma once
#include "Enemy.h"

class Ghost : public Enemy
{
public:
	bool isExist;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject * other);
	void restore(BaseObject* obj);
	Ghost();
	~Ghost();
};

