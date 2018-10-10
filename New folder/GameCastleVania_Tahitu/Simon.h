#pragma once
#include "MovableObject.h"
#include "Whip.h"
#include "WhipSitDown.h"
#include "Stairs.h"

enum SIMON_ACTION
{
	SA_STAND,
	SA_WALK,
	SA_STAND_ATTACK,
	SA_JUMP_ATTACK,
	SA_JUMP,
	SA_DAMAGED,
	SA_SITDOWN,
	SA_SITDOWN_ATTACK,
	SA_UPSTAIR,
	SA_DOWNSTAIR,
	SA_UPSTAIR_ATTACK,
	SA_DOWNSTAIR_ATTACK,
	SA_PICKUP_ITEM,
	SA_RANGE_ATTACK,
	SA_STOP_WATCH,
	SA_INVISIBLE,
	SA_DEATH
};

enum WEAPON_TYPE
{
	WT_DEFAULT,
	WT_DAGGER,
	WT_BOOMERANG,
	WT_HOLY_WATER,
	WT_STOPWATCH,
	WT_THROWING_AXE
};

class Simon : public MovableObject
{
	static Simon* instance;
public:
	static Simon* getInstance();

	WEAPON_TYPE weaponType;
	GameTimeLoop timeRangeWeaponAppear;
	GameTimeLoop timePickUpItem;
	GameTimeLoop timeDeath;
	int numberWeaponAppear;
	int numberAppear;
	bool* doorUpdating;
	bool invisible; 
	bool invisibilityPoint;
	int score;
	bool onHit;
	int updateX;
	int numberOfAttacks;
	int stage;
	int numberOfAlive;
	bool onPickUpItem;
	bool allowDraw;
	bool isDeath;
	int level;
	bool onAreaBoss;

	void setOnHit(bool newOnHit);
	void update();
	bool updateDeath();
	void updateInvisible();
	bool updatePause();
	void updateDirection();
	void updateChangeAnimation();
	void updateAfter();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void draw();
	void updateLocation();
	void changeAction(int newAction);

#pragma region Go to
	bool onStair;
	bool onGoTo;
	Stairs* stairInterserct;
	float xDestination, yDestination;
	float vxStair, vyStair;
	Direction directionStair;

	void initGoTo(float xDestination, float yDestination, float duration, Stairs* stairInterserct);
	void goUp(Stairs* stairInterserct);
	void goDown(Stairs* stairInterserct);
	void updateGoTo();
	void atDestination();
#pragma endregion

	Simon();
	~Simon();
};

