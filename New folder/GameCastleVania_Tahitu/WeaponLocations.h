#pragma once
#include "Point.h"

class WeaponLocations
{
	static WeaponLocations* instance;
public:
	static WeaponLocations* getInstance();

	Point pts[3];
	Point ptsSitDown[3];

	WeaponLocations();
	~WeaponLocations();
};

