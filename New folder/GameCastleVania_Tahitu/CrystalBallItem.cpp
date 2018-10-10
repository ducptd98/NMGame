#include "CrystalBallItem.h"
#include "Simon.h"
#include "Medusa.h"

void CrystalBallItem::update()
{
	DrawableObject::update();

	if (Medusa::isDeath && time.isTerminated() && !isPickUp)
	{
		isPickUp = true;
		time.start();
	}

	if (time.canCreateFrame())
	{
		alive = true;
		dy = 0.7f;
	}

	if (isNextLevel && timeNextLevel.canCreateFrame())
	{
		isNextLevel = false;
		SIMON->level++;
	}
}

void CrystalBallItem::restore(BaseObject * obj)
{
	Item::restore(obj);
	curAnimation = IA_CRYSTAL_BALL;
	nextAnimation = IA_CRYSTAL_BALL;
	alive = false;
	isPickUp = false;
}

CrystalBallItem::CrystalBallItem()
{
	itemType = IT_CRYSTAL_BALL;
	curAnimation = IA_CRYSTAL_BALL;
	nextAnimation = IA_CRYSTAL_BALL;
	alive = false;
	time.init(3, 1);
	isPickUp = false;
}

CrystalBallItem::~CrystalBallItem()
{
}
