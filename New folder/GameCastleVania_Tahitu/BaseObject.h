#pragma once
#include "Sprite.h"
#include "GameTime.h"
#include "Constant.h"
#include "Box.h"
#include "OldRestore.h"
#include "GameSound.h"

extern void* operator new(std::size_t sz);

enum COLLISION_TYPE
{
	CT_PLAYER,
	CT_GROUND,
	CT_STAIRS,
	CT_PREVENTMOVECAMERA,
	CT_ENEMY,
	CT_ITEM,
	CT_DOOR,
	CT_WHIP,
	CT_BRIDGE,
	CT_WEAPON,
	CT_BRICK
};

class BaseObject : public Box, public OldRestore
{
public:
	COLLISION_TYPE collisionType;
	int id;
	bool isCollisionCross;
	bool isCollision;
	bool alive;
	int life;
	bool allowDelete;

	virtual void update();
	virtual void draw();
	virtual void onCollision(BaseObject* other, int nx, int ny);
	virtual void onAABBCheck(BaseObject* other);
	virtual void updateLocation();
	RectF oldRect();

	BaseObject();
	~BaseObject();
};

