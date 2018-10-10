#include "Trap.h"
#include "GameState.h"
#include "Simon.h"

void Trap::update()
{
	if (GameState::curState == PAUSE_ENEMY)
		return;

	if (!isReturn)
	{
		if (gameTimeLoop.canCreateFrame())
		{
			sprite->animates[0].frames[0].y -= 9;
			height += 9;
		}

		if (gameTimeLoop.isTerminated())
		{
			isReturn = true;
			gameTimeLoop.start();
		}
	}
	else
	{
		if (gameTimeLoop.canCreateFrame())
		{
			sprite->animates[0].frames[0].y += 9;
			height -= 9;
		}

		if (gameTimeLoop.isTerminated())
		{
			isReturn = false;
			gameTimeLoop.start();
		}
	}
}

void Trap::onAABBCheck(BaseObject * other)
{
	if (other == SIMON)
	{
		SIMON->isDeath = true;
		SIMON->changeAction(SA_DEATH);
		SIMON->curFrame = 0;
		SIMON->dx = 0;
		SIMON->dy = 0;
	}
}

void Trap::restore(BaseObject * obj)
{
	DrawableObject::restore(obj);
	height = 18;
	sprite->animates[0].frames[0].y = 18;
	initTime();
}

Trap::Trap()
{
	collisionType = CT_BRIDGE;
	isReturn = false;
}

Trap::~Trap()
{
}
