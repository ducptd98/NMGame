#pragma once
#include "MovableObject.h"

class Bridge : public MovableObject
{
public:
	void update();
	void onCollision(BaseObject* other, int nx, int ny);

	Bridge();
	~Bridge();
};

