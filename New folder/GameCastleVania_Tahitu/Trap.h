#pragma once
#include "DrawableObject.h"

class Trap : public DrawableObject
{
public:
	bool isReturn;
	virtual void initTime() {};
	virtual void update();
	virtual void onAABBCheck(BaseObject* other);
	void restore(BaseObject* obj);
	Trap();
	~Trap();
};

