#pragma once
#include "DrawableObject.h"

enum LIFE_TYPE
{
	LT_PLAYER,
	LT_ENEMY,
	LT_HALF_PLAYER,
	LT_HALF_ENEMY,
	LT_EMPTY
};

class Life : public DrawableObject
{
public:
	virtual void next(int& curFrame);
	virtual void draw();
	void updateLocation();

	Life();
	~Life();
};

