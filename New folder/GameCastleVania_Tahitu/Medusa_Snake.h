#pragma once
#include "Enemy.h"
#include "List.h"

class Medusa_Snake : public Enemy
{
public:
	static List<Medusa_Snake*>* listMedusa_Snake;
	static List<Medusa_Snake*>* getListMedusa_Snake();

	bool allowDelete;
	bool isCollisionSIMON;

	void update();
	void draw();
	void onAABBCheck(BaseObject* other);
	void onCollision(BaseObject * other, int nx, int ny);

	Medusa_Snake(int xMedusa, int yMedusa, Direction direction);
	Medusa_Snake();
	~Medusa_Snake();
};

