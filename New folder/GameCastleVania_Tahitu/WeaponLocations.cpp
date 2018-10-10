#include "WeaponLocations.h"

WeaponLocations* WeaponLocations::instance = 0;
WeaponLocations* WeaponLocations::getInstance()
{
	if (instance == 0)
		instance = new WeaponLocations();
	return instance;
}

WeaponLocations::WeaponLocations()
{
	pts[0].init(24, 7);
	pts[1].init(17, 5);
	pts[2].init(0, 15);

	ptsSitDown[0].init(25, 15);
	ptsSitDown[1].init(16, 12);
	ptsSitDown[2].init(0, 21);
}

WeaponLocations::~WeaponLocations()
{
}
