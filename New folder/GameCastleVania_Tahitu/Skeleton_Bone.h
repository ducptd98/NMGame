#pragma once
#include "Weapon.h"

class Skeleton_Bone : public Weapon
{
public:
	static List<Skeleton_Bone*>* listSkeleton_Bone;
	static List<Skeleton_Bone*>* getListSkeleton_Bone();

	int angle;
	int damage;
	bool allowDelete;
	bool isCollisionSIMON;
	void update();
	void draw();
	void onAABBCheck(BaseObject* other);
	GameTimeLoop timeDeath;

	Skeleton_Bone(int x, int y, Direction direction, int vy);
	Skeleton_Bone();
	~Skeleton_Bone();
};

