#include "Brick.h"
#include "Whip.h"
#include "Simon.h"

void Brick::onAABBCheck(BaseObject * other)
{
	if (((other == WHIP && WHIP->canAttack) || (other == WHIPSITDOWN && WHIPSITDOWN->canAttack) || other->collisionType == CT_WEAPON) && curAnimation == BA_DEFAULT)
	{
		if (SIMON->weaponType != WT_HOLY_WATER && SIMON->weaponType != WT_BOOMERANG)
			other->allowDelete = true;

		switch (brickType)
		{
		case BT_PORK_CHOP:
			curAnimation = BA_PORK_CHOP;
			nextAnimation = BA_PORK_CHOP;
			dy = 1;
			break;
		case BT_DOUBLE_SHOT:
			curAnimation = BA_DOUBLE_SHOT;
			nextAnimation = BA_DOUBLE_SHOT;
			dy = 1;
			break;
		case BT_TRIPLE_SHOT:
			curAnimation = BA_TRIPLE_SHOT;
			nextAnimation = BA_TRIPLE_SHOT;
			dy = 1;
			break;
		case BT_BLACK:
			curAnimation = BA_BLACK;
			nextAnimation = BA_BLACK;
			break;
		default:
			break;
		}

		switch (brickType3)
		{
		case BT3_PORK_CHOP:
			curAnimation = BA_PORK_CHOP;
			nextAnimation = BA_PORK_CHOP;
			dy = 1;
			break;
		case BT3_DOUBLE_SHOT:
			curAnimation = BA_DOUBLE_SHOT;
			nextAnimation = BA_DOUBLE_SHOT;
			dy = 1;
			break;
		case BT3_TRIPLE_SHOT:
			curAnimation = BA_TRIPLE_SHOT;
			nextAnimation = BA_TRIPLE_SHOT;
			dy = 1;
			break;
		case BT3_BLACK:
			curAnimation = BA_BLACK;
			nextAnimation = BA_BLACK;
			break;
		default:
			break;
		}
	}

	if (other == SIMON && curAnimation != BA_DEFAULT)
	{
		switch (brickType)
		{
		case BT_PORK_CHOP:
			SIMON->life += 6;
			if (SIMON->life > 16)
				SIMON->life = 16;
			break;
		case BT_DOUBLE_SHOT:
			if (SIMON->weaponType == WT_STOPWATCH || SIMON->weaponType == WT_DEFAULT)
				SIMON->score += 700;
			else
			{
				if (SIMON->numberAppear == 1)
				{
					SIMON->numberWeaponAppear = 2;
					SIMON->numberAppear = 2;
				}
				else
				{
					SIMON->numberWeaponAppear = 3;
					SIMON->numberAppear = 3;
				}
			}
			break;
		case BT_TRIPLE_SHOT:
			if (SIMON->weaponType == WT_STOPWATCH)
				SIMON->score += 700;
			else
			{
				SIMON->numberWeaponAppear = 3;
				SIMON->numberAppear = 3;
			}
			break;
		default:
			break;
		}

		switch (brickType3)
		{
		case BT3_PORK_CHOP:
			SIMON->life += 6;
			if (SIMON->life > 16)
				SIMON->life = 16;
			break;
		case BT3_DOUBLE_SHOT:
			if (SIMON->weaponType == WT_STOPWATCH)
				SIMON->score += 700;
			else
			{
				if (SIMON->numberAppear == 1)
				{
					SIMON->numberWeaponAppear = 2;
					SIMON->numberAppear = 2;
				}
				else
				{
					SIMON->numberWeaponAppear = 3;
					SIMON->numberAppear = 3;
				}
			}
			break;
		case BT3_TRIPLE_SHOT:
			if (SIMON->weaponType == WT_STOPWATCH)
				SIMON->score += 700;
			else
			{
				SIMON->numberWeaponAppear = 3;
				SIMON->numberAppear = 3;
			}
			break;
		default:
			break;
		}

		alive = false;
	}
}

void Brick::onCollision(BaseObject * other, int nx, int ny)
{
	if (ny == -1)
		SIMON->isOnGround = true;

	if (curAnimation == BA_DEFAULT && ny != 1 && other == SIMON)
		COLLISION->preventMove(other, this);

	if (curAnimation != BA_DEFAULT && other->collisionType == CT_GROUND && ny != 1)
		COLLISION->preventMove(this, other);
}

void Brick::restore(BaseObject * obj)
{
	dy = 0;
	vy = 0;
	DrawableObject::restore(obj);
}

Brick::Brick()
{
	collisionType = CT_BRICK;
	direction = Left;
}

Brick::~Brick()
{
}
