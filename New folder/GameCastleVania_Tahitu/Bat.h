#pragma once
#include "Enemy.h"

class Bat : public Enemy
{
public:
	int oldYSimon;
	bool isFly;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject * obj);

	Bat();
	~Bat();
};

