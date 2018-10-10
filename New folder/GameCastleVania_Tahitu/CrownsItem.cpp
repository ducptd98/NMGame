#include "CrownsItem.h"
#include "Simon.h"

void CrownsItem::update()
{
	DrawableObject::update();

	if (SIMON->right() >= 2030 && checkPickUp)
	{
		checkPickUp = false;
		alive = true;
		curAnimation = IA_CROWNS;
		nextAnimation = IA_CROWNS;
	}
}

void CrownsItem::restore(BaseObject * obj)
{
	Item::restore(obj);
	alive = false;
}

CrownsItem::CrownsItem()
{
	itemType = IT_CROWNS;
	alive = false;
	checkPickUp = true;
}

CrownsItem::~CrownsItem()
{
}
