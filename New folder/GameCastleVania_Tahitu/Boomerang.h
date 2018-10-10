#pragma once
#include "Weapon.h"

class Boomerang : public Weapon
{
public:
	static List<Boomerang*>* boomerangs;
	static List<Boomerang*>* getBoomerangs();

	bool isReturn;

	void update();
	void draw();
	void onAABBCheck(BaseObject* other);
	void setReturn();

	Boomerang();
	~Boomerang();
};

