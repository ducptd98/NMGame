#pragma once
#include "Weapon.h"

class HolyWater : public Weapon
{
public:
	static List<HolyWater*>* holyWaters;
	static List<HolyWater*>* getHolyWaters();

	bool isCollisonGround;

	void updateVerlocity();
	void update();
	void draw();
	void onAABBCheck(BaseObject* other);
	void onCollision(BaseObject* other, int nx, int ny);

	HolyWater();
	~HolyWater();
};

