#include "MedusaHead.h"
#include "MedusaHead_List.h"
#include "Map.h"

void MedusaHead::update()
{
	if (x < CAMERA->left() - 20 || x > CAMERA->right() + 20)
		alive = false;

	if (alive)
	{
		if (timeCreateMedusaHead->canCreateFrame())
			MEDUSAHEADS->_Add(new MedusaHead_List());

		if (timeCreateMedusaHead->isTerminated())
			timeCreateMedusaHead->start();
	}
}

void MedusaHead::draw()
{
}

void MedusaHead::onCollision(BaseObject * other, int nx, int ny)
{
	Enemy::onCollision(other, nx, ny);
}

void MedusaHead::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	timeCreateMedusaHead = new GameTimeLoop();
	timeCreateMedusaHead->init(2.3, 1);
	timeCreateMedusaHead->start();
}

MedusaHead::MedusaHead()
{
	timeCreateMedusaHead = new GameTimeLoop();
	timeCreateMedusaHead->init(2.3, 1);
	timeCreateMedusaHead->start();
}

MedusaHead::~MedusaHead()
{

}
