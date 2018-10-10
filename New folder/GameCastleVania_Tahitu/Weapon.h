#pragma once
#include "DrawableObject.h"
#include "List.h"
#include "Camera.h"
#include "WeaponLocations.h"

class Weapon : public DrawableObject
{
public:
	virtual void update();
	virtual void draw();
	virtual void onAABBCheck(BaseObject* other);

	Weapon();
	~Weapon();
};

