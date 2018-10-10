#pragma once
#include "BaseObject.h"

enum STAIR_TYPE
{
	ST_CHANGE_STAGE = -402,
	ST_TOP = -202,
	ST_BOTTOM = -102,
	ST_LEFT_BOTTOM = -502,
	ST_LEFT_TOP = -602
};

class Stairs : public BaseObject
{
public:
	Direction directionStair;

	void calSimonNewPosMidWidth(int& x, int& y);
	void calSimonNewPosMidHeight(int& x, int& y);
	void onAABBCheck(BaseObject* other);
	void getFromObject(BaseObject* obj);

	Stairs();
	~Stairs();
};

