#pragma once
#include "DrawableObject.h"

enum ITEM_TYPE
{
	IT_DEFAULT,
	IT_BOOMERANG,
	IT_DAGGER,
	IT_HOLY_WATER,
	IT_STOP_WATCH,
	IT_THROWING_AXE
};

class WeaponType : public DrawableObject
{
public:
	void draw();
	void update();
	void updateLocation();

	WeaponType();
	~WeaponType();
};

