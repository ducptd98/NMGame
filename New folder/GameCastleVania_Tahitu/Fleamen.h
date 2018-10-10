#pragma once
#include "Enemy.h"

class Fleamen : public Enemy
{
public:
	bool isJumping;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject* obj);

	Fleamen();
	~Fleamen();
};

