#pragma once
#include "MovableObject.h"
#include "EffectAttack.h"

class Enemy : public MovableObject
{
public:
	int damage;
	int score;
	bool damaged;
	EffectAttack* effect;
	GameTimeLoop timeDeath;

	virtual void update();
	virtual void draw();
	virtual void onCollision(BaseObject* other, int nx, int ny);
	virtual void onAABBCheck(BaseObject* other);
	virtual void restore(BaseObject* obj);

	Enemy(void);
	~Enemy(void);
};

