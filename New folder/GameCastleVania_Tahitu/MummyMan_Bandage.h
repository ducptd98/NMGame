#pragma once
#include "Weapon.h"

class MummyMan_Bandage : public Weapon
{
public:
	static List<MummyMan_Bandage*>* listMummyMan_Bandage;
	static List<MummyMan_Bandage*>* getListMummyMan_Bandage();

	int angle;
	int damage;
	bool allowDelete;
	bool isCollisionSIMON;
	GameTimeLoop timeDeath;

	void update();
	void draw();
	void onAABBCheck(BaseObject* other);

	MummyMan_Bandage(int xMummyMan, int yMummyMan, Direction directionMummyMan);
	MummyMan_Bandage();
	~MummyMan_Bandage();
};

