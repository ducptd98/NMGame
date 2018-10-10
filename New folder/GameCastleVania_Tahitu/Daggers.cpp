#include "Daggers.h"

List<Daggers*>* Daggers::daggers = 0;
List<Daggers*>* Daggers::getDaggers()
{
	if (daggers == 0)
		daggers = new List<Daggers*>();
	return daggers;
}

void Daggers::update()
{
	Weapon::update();

	if ((x + dx < CAMERA->left() && dx < 0) || (right() + dx > CAMERA->right() && dx > 0))
		allowDelete = true;
}

void Daggers::draw()
{
	Weapon::draw();
}

void Daggers::onAABBCheck(BaseObject * other)
{
	Weapon::onAABBCheck(other);
}

Daggers::Daggers()
{
	sprite = SPRITEMANAGER->sprites[SPR_DAGGER];
	getDaggers()->_Add(this);
}

Daggers::~Daggers()
{
}
