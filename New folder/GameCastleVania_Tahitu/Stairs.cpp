#include "Stairs.h"
#include "Simon.h"
#include "KeyGame.h"
#include "Stage.h"

void Stairs::calSimonNewPosMidWidth(int& x, int& y)
{
	if (directionStair == Right)
		x = xCenter() - SIMON->width;
	else
		x = xCenter();

	y = bottom() - SIMON->height;
}

void Stairs::calSimonNewPosMidHeight(int& x, int& y)
{
	x = right() - SIMON->width;
	y = yCenter() - SIMON->height;
}

void Stairs::onAABBCheck(BaseObject * other)
{
	if (other == SIMON && id == ST_CHANGE_STAGE)
	{
		if (SIMON->vy < 0 && SIMON->onStair)
		{
			Stage::next();
			SIMON->onGoTo = false;
			SIMON->y = top() - SIMON->height - 8;
			SIMON->x = right() - SIMON->width;
		}

		if (SIMON->vy > 0 && SIMON->onStair)
		{
			Stage::prev();
			SIMON->onGoTo = false;
			if (SIMON->direction == Right)
			{
				SIMON->y = bottom() + 8 - SIMON->height;
				SIMON->x = left() + SIMON->width - 1;
			}
			else
			{
				SIMON->y = bottom() + 8 - SIMON->height;
				SIMON->x = left() - SIMON->width - 1;
			}
		}
	}

	if (!KEY->keyStair)
		return;

	if (other == SIMON)
	{
		if ((id == ST_BOTTOM || id == ST_LEFT_BOTTOM) && KEY->keyBeginStair && !SIMON->onStair && SIMON->isOnGround)
		{
			SIMON->onStair = true;
			int xDestination, yDestination;
			calSimonNewPosMidWidth(xDestination, yDestination);
			SIMON->initGoTo(xDestination, yDestination, 0.2, this);
		}

		if (!SIMON->onStair || SIMON->onGoTo)
			return;

		if (KEY->keyUp || (KEY->keyRight && SIMON->directionStair == Right) || (KEY->keyLeft && SIMON->directionStair == Left))
		{
			SIMON->goUp(this);
			return;
		}

		if (KEY->keyDown || (KEY->keyRight && SIMON->directionStair == Left) || (KEY->keyLeft && SIMON->directionStair == Right))
			SIMON->goDown(this);
	}
}

void Stairs::getFromObject(BaseObject * obj)
{
	OldRestore::getFromObject(obj);
	directionStair = Right;

	if (id / 100 <= -5)
		directionStair = Left;
}

Stairs::Stairs()
{
	collisionType = CT_STAIRS;
}

Stairs::~Stairs()
{
}
