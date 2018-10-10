#pragma once
#include "Enemy.h"
#include "List.h"

class MedusaHead : public Enemy
{
public:
	GameTimeLoop* timeCreateMedusaHead;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject * obj);

	MedusaHead();
	~MedusaHead();
};

