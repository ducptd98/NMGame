#pragma once
#include "Life.h"

class LifePlayer
{
public:
	Life* life;

	void draw();
	void update();

	LifePlayer();
	~LifePlayer();
};

