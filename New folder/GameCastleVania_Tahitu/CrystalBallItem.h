#pragma once
#include "Item.h"

class CrystalBallItem : public Item
{
public:
	GameTimeLoop time;
	bool isPickUp;

	void update();
	void restore(BaseObject* obj);

	CrystalBallItem();
	~CrystalBallItem();
};

