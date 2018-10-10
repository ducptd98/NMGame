#pragma once
#include "MovableObject.h"

enum BRICK_ACTION
{
	BA_DEFAULT,
	BA_PORK_CHOP,
	BA_DOUBLE_SHOT,
	BA_TRIPLE_SHOT,
	BA_BLACK
};

enum BRICK_TYPE
{
	BT_PORK_CHOP = 123,
	BT_DOUBLE_SHOT = 223,
	BT_TRIPLE_SHOT = 323,
	BT_BLACK = 423
};

enum BRICK_TYPE_3
{
	BT3_PORK_CHOP = 129,
	BT3_DOUBLE_SHOT = 229,
	BT3_TRIPLE_SHOT = 329,
	BT3_BLACK = 429
};

class Brick : public MovableObject
{
public:
	BRICK_TYPE brickType;
	BRICK_TYPE_3 brickType3;

	virtual void onAABBCheck(BaseObject* other);
	virtual void onCollision(BaseObject* other, int nx, int ny);
	virtual void restore(BaseObject* obj);

	Brick();
	~Brick();
};

