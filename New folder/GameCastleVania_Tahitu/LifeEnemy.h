#pragma once
#include "Life.h"

class LifeEnemy
{
public:
	Life* life;

	void draw();
	void update();

	LifeEnemy();
	~LifeEnemy();
};

