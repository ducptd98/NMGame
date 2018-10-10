#pragma once
#include "MovableObject.h"

enum ITEM_ACTION
{
	IA_DEFAULT,
	IA_WHIP_UPGRADE,
	IA_BOOMERANG,
	IA_DAGGER,
	IA_HOLY_WATER,
	IA_SMALL_HEART,
	IA_LARGE_HEART,
	IA_RED_MONEY_BAG,
	IA_PURPLE_MONEY_BAG,
	IA_WHITE_MONEY_BAG,
	IA_STOP_WATCH,
	IA_CROSS,
	IA_INVISIBILITY_POTION,
	IA_BONUSES,
	IA_CRYSTAL_BALL,
	IA_CROWNS,
	IA_CHESTS,
	IA_THROWING_AXE
};

enum ITEM_TYPE
{
	IT_WHIP_UPGRADE = 119,
	IT_BOOMERANG = 219,
	IT_DAGGER = 319,
	IT_HOLY_WATER = 419,
	IT_SMALL_HEART = 519,
	IT_LARGE_HEART = 619,
	IT_RED_MONEY_BAG = 719,
	IT_PURPLE_MONEY_BAG = 819,
	IT_WHITE_MONEY_BAG = 919,
	IT_STOP_WATCH = 1019,
	IT_CROSS = 1119,
	IT_INVISIBILITY_POTION = 1219,
	IT_THROWING_AXE = 1319,
	IT_BONUSES = 1619,
	IT_CRYSTAL_BALL = 1719,
	IT_CROWNS = 1819,
	IT_CHESTS = 1919,
};

class Item : public MovableObject
{
public:
	ITEM_TYPE itemType;
	bool isNextLevel;
	GameTimeLoop timeNextLevel;

	virtual void onAABBCheck(BaseObject* other);
	virtual void onCollision(BaseObject* other, int nx, int ny);
	virtual void restore(BaseObject* obj);
	virtual void update();

	Item();
	~Item();
};

