#include "Boomerang.h"

List<Boomerang*>* Boomerang::boomerangs = 0;
List<Boomerang*>* Boomerang::getBoomerangs()
{
	if (boomerangs == 0)
		boomerangs = new List<Boomerang*>();
	return boomerangs;
}

void Boomerang::update()
{
	vy = 0;
	dy = 0;
	Weapon::update();

	if (!isReturn)
		if ((x + dx < CAMERA->left() && dx < 0) || (right() + dx > CAMERA->right() && dx > 0))
			setReturn();

	if (!isReturn)
		if ((dx > 0 && (x + dx >= oldX + 144)) || (dx < 0 && (x + dx <= oldX - 144)))
			setReturn();
}

void Boomerang::draw()
{
	Weapon::draw();
}

void Boomerang::onAABBCheck(BaseObject * other)
{
	Weapon::onAABBCheck(other);

	if (other == SIMON && isReturn)
		allowDelete = true;
}

void Boomerang::setReturn()
{
	isReturn = true;
	dx = -dx;
}

Boomerang::Boomerang()
{
	sprite = SPRITEMANAGER->sprites[SPR_BOOMERANG];
	oldX = x;
	getBoomerangs()->_Add(this);
	isReturn = false;
}

Boomerang::~Boomerang()
{
}
