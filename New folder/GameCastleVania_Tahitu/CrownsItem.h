#pragma once
#include "Item.h"

class CrownsItem : public Item
{
public:
	bool checkPickUp;

	void update();
	void restore(BaseObject* obj);

	CrownsItem();
	~CrownsItem();
};

