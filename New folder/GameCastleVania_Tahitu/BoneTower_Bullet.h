#pragma once
#include "Weapon.h"

class BoneTower_Bullet : public Weapon
{
public:
	static List<BoneTower_Bullet*>* listBoneTower_Bullet;
	static List<BoneTower_Bullet*>* getListBoneTower_Bullet();

	bool allowDelete;
	bool isCollisionSIMON;
	GameTimeLoop timeDeath;

	void update();
	void draw();
	void onAABBCheck(BaseObject* other);

	BoneTower_Bullet(int x, int y, Direction direction);
	BoneTower_Bullet();
	~BoneTower_Bullet();
};

