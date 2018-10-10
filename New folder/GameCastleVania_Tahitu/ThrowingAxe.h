#pragma once
#include "Weapon.h"

class ThrowingAxe : public Weapon
{
public:
	static List<ThrowingAxe*>* throwingAxes;
	static List<ThrowingAxe*>* getThrowingAxes();

	void updateVerlocity();
	void update();
	void draw();
	void onAABBCheck(BaseObject* other);

	ThrowingAxe();
	~ThrowingAxe();
};

