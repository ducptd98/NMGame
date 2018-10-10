#pragma once
#include "Weapon.h"

class Daggers : public Weapon
{
public:
	static List<Daggers*>* daggers;
	static List<Daggers*>* getDaggers();

	void update();
	void draw();
	void onAABBCheck(BaseObject* other);

	Daggers();
	~Daggers();
};

