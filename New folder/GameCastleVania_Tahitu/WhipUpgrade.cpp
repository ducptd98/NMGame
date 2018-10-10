#include "WhipUpgrade.h"
#include "Whip.h"

void WhipUpgrade::update()
{
	if (WHIP->index < 4)
		itemType = IT_WHIP_UPGRADE;
	else
		itemType = IT_SMALL_HEART;

	Item::update();
}

WhipUpgrade::WhipUpgrade()
{
	itemType = IT_WHIP_UPGRADE;
}

WhipUpgrade::~WhipUpgrade()
{
}
