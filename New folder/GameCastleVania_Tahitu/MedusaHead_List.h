#pragma once
#include "Enemy.h"
#include "List.h"

class MedusaHead_List : public Enemy
{
public:
	static List<MedusaHead_List*>* listMedusaHead_List;
	static List<MedusaHead_List*>* getListMedusaHead_List();

	int angle;
	bool allowDelete;
	bool isCollisionSIMON;

	void update();
	void draw();
	void onAABBCheck(BaseObject* other);
	void onCollision(BaseObject * other, int nx, int ny);

	MedusaHead_List();
	~MedusaHead_List();
};

