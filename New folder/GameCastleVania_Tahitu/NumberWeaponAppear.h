#pragma once
#include "DrawableObject.h"

enum NUMBER_TYPE
{
	NT_DEFAULT,
	NT_DOUBLESHOT,
	NT_TRIPLESHOT
};

class NumberWeaponAppear : public DrawableObject
{
public:
	void draw();
	void update();
	void updateLocation();

	NumberWeaponAppear();
	~NumberWeaponAppear();
};

