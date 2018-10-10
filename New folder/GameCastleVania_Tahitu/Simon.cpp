#include "Simon.h"
#include "SpriteManager.h"
#include "KeyGame.h"
#include "TileMap.h"
#include "Stage.h"
#include "Boomerang.h"
#include "HolyWater.h"
#include "GameState.h"
#include "StopWatch.h"
#include "Daggers.h"
#include "ThrowingAxe.h"

Simon* Simon::instance = 0;
Simon* Simon::getInstance()
{
	if (instance == 0)
		instance = new Simon();

	return instance;
}

void Simon::setOnHit(bool newOnHit)
{
	if (newOnHit && !onStair)
	{
		vy = -120;
		vx = -60 * direction;
	}

	onHit = newOnHit;
}

void Simon::update()
{
	if (x < 64 && y < 176 && !onAreaBoss && level == 2)
	{
		Stage::next();
		onAreaBoss = true;
	}

	if (x > 3500 && y < 192 && !onAreaBoss && level == 3)
	{
		Stage::next();
		onAreaBoss = true;
	}

	if (updateDeath())
		return;

	timeRangeWeaponAppear.canCreateFrame();

	updateInvisible();

	if (!updatePause())
		return;

	updateDirection();

	updateChangeAnimation();

	MovableObject::update();

	updateAfter();
}

bool Simon::updateDeath()
{
	if (isDeath)
	{
		timeDeath.canCreateFrame();
		vy = 0;
		dy = 0;
		dx = 0;

		if (timeDeath.isTerminated())
		{
			alive = false;
			isDeath = false;
		}

		return true;
	}

	if (bottom() + dx >= Stage::curStage->bottom() && dy > 0 && !onStair)
	{
		isDeath = true;
		y += height;
		//vy = -180;
		changeAction(SA_DEATH);
	}

	return false;
}

void Simon::updateInvisible()
{
	if (invisible)
	{
		if (gameTimeLoop.canCreateFrame())
			allowDraw = !allowDraw;

		if (gameTimeLoop.isTerminated())
		{
			allowDraw = true;
			setOnHit(false);
			invisible = false;
		}
	}

	if (invisibilityPoint)
	{
		curAnimation = SA_INVISIBLE;
		curFrame = (curFrame + 1) % 2;
		gameTimeLoop.canCreateFrame();

		if (gameTimeLoop.isTerminated())
			invisibilityPoint = false;
	}

	if (onPickUpItem)
	{
		if (timePickUpItem.canCreateFrame())
		{
			curAnimation = SA_PICKUP_ITEM;
			curFrame = (curFrame + 1) % 3;
		}

		if (timePickUpItem.isTerminated())
		{
			onPickUpItem = false;
			GameState::curState = RUN;
		}
	}
}

bool Simon::updatePause()
{
	if (onPickUpItem)
		return false;

	if (doorUpdating != 0 && *doorUpdating)
	{
		DrawableObject::update();
		return false;
	}

	if (onGoTo)
	{
		updateGoTo();
		return false;
	}

	if (onStair)
	{
		if (KEY->keyAttackPress)
		{
			if ((direction == Right && directionStair == Right) || (direction == Left && directionStair == Left))
				changeAction(SA_UPSTAIR_ATTACK);
			else 
				changeAction(SA_DOWNSTAIR_ATTACK);

			WHIP->update();
		}
		else
			if ((direction == Right && directionStair == Right) || (direction == Left && directionStair == Left))
				changeAction(SA_UPSTAIR);
			else
				changeAction(SA_DOWNSTAIR);

		if (!pauseAnimation)
		{
			if (delayAnimation.canCreateFrame())
			{
				if (curFrame == sprite->animates[curAnimation].nFrame - 1)
				{
					curAnimation = nextAnimation;
					curFrame = sprite->animates[curAnimation].nFrame - 1;
				}

				sprite->animates[curAnimation].next(curFrame);
			}
		}

		if (curAnimation == SA_UPSTAIR || curAnimation == SA_DOWNSTAIR)
			curFrame = 1;

		return false;
	}

	if (onHit)
	{
		MovableObject::update();
		WHIPSITDOWN->x = 0;
		WHIPSITDOWN->y = 0;
		WHIP->x = 0;
		WHIP->y = 0;
		return false;
	}

	return true;
}

void Simon::updateDirection()
{
	if (KEY->keyLeft && curAnimation != SA_STAND_ATTACK && curAnimation != SA_SITDOWN_ATTACK)
		direction = Left;

	if (KEY->keyRight && curAnimation != SA_STAND_ATTACK && curAnimation != SA_SITDOWN_ATTACK)
		direction = Right;

	if (KEY->keyMove && ((curAnimation != SA_STAND_ATTACK && curAnimation != SA_SITDOWN  && curAnimation != SA_SITDOWN_ATTACK && curAnimation != SA_RANGE_ATTACK) || !isOnGround))
		vx = SIMON_VX_GO * direction;
	else
		vx = 0;
}

void Simon::updateChangeAnimation()
{
	if (isOnGround)
	{
		if (KEY->keyJumpPress && curAnimation != SA_STAND_ATTACK && curAnimation != SA_SITDOWN_ATTACK)
			vy = -150;
		else
		{
			if (KEY->keyRangeAttack && weaponType != WT_DEFAULT && weaponType != WT_STOPWATCH && numberOfAttacks > 0 && numberWeaponAppear > 0)
			{
				changeAction(SA_RANGE_ATTACK);

				if (timeRangeWeaponAppear.isTerminated())
				{
					switch (weaponType)
					{
					case WT_DEFAULT:
						break;
					case WT_DAGGER:
						GAMESOUND->play(DAGGER_THROW, false);
						new Daggers();
						break;
					case WT_BOOMERANG:
						GAMESOUND->play(DAGGER_THROW, false);
						new Boomerang();
						break;
					case WT_THROWING_AXE:
						GAMESOUND->play(AXE_TOSS, false);
						new ThrowingAxe();
						break;
					case WT_HOLY_WATER:
						GAMESOUND->play(HOLY_WATER, false);
						new HolyWater();
						break;
					case WT_STOPWATCH:
						break;
					default:
						break;
					}

					numberWeaponAppear--;
					numberOfAttacks--;
					timeRangeWeaponAppear.start();
				}
			}
			else
			{
				if (KEY->keyRangeAttack && weaponType == WT_STOPWATCH && !STOPWATCH->onActive)
					changeAction(SA_STOP_WATCH);
				else
				{
					if (KEY->keySitDownAttack)
						changeAction(SA_SITDOWN_ATTACK);
					else
					{
						if (KEY->keyAttackPress)
							changeAction(SA_STAND_ATTACK);
						else
						{
							if (KEY->keyDown)
								changeAction(SA_SITDOWN);
							else
							{
								if (KEY->keyJumpPress)
									changeAction(SA_JUMP);
								else
								{
									if (!KEY->keyMove)
										changeAction(SA_STAND);
									else
										changeAction(SA_WALK);
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if (curAnimation == SA_WALK && nextAnimation == SA_JUMP)
		{
			curAnimation = nextAnimation;
			curFrame = 0;
		}
		else
		{
			if (KEY->keyAttackPress)
				changeAction(SA_STAND_ATTACK);
			else
			{
				if (vy < 40)
					changeAction(SA_JUMP);
				else
					changeAction(SA_STAND);
			}
		}
	}

	if (curAnimation == SA_SITDOWN_ATTACK)
		WHIPSITDOWN->update();
	else
	{
		WHIPSITDOWN->x = 0;
		WHIPSITDOWN->y = 0;
	}

	if (curAnimation == SA_STAND_ATTACK)
		WHIP->update();
	else
	{
		WHIP->x = 0;
		WHIP->y = 0;
	}

	if (curAnimation == SA_STOP_WATCH && weaponType == WT_STOPWATCH)
		STOPWATCH->onActive = true;

	if (STOPWATCH->onActive == true && numberOfAttacks > 0)
		STOPWATCH->update();
}

void Simon::updateAfter()
{
	if (curAnimation == SA_WALK && (nextAnimation == SA_STAND_ATTACK || nextAnimation == SA_SITDOWN))
	{
		curAnimation = nextAnimation;
		curFrame = 0;
	}
}

void Simon::onCollision(BaseObject * other, int nx, int ny)
{
	if (!onStair)
		MovableObject::onCollision(other, nx, ny);
	else
	{
		if (ny == -1 && other->collisionType == CT_GROUND && curAnimation == SA_DOWNSTAIR && dy > 0)
		{
			MovableObject::onCollision(other, nx, ny);
			onStair = false;
			onGoTo = false;
		}
	}

	if (onHit && isOnGround)
	{
		if (life <= 0)
		{
			changeAction(SA_DEATH);
			curFrame = 0;
			dx = 0;
			dy = 0;
			isDeath = true;
		}
		else
		{
			curAnimation = SA_SITDOWN;
			curFrame = 0;
			invisible = true;
		}

		setOnHit(false);
		vx = 0;
	}

	if ((other->id == ST_TOP || other->id == ST_LEFT_TOP || other->id == ST_CHANGE_STAGE) && ny == -1 && !onStair)
	{
		isOnGround = true;

		if (other->id == ST_TOP || other->id == ST_LEFT_TOP)
			COLLISION->preventMove(this, other);

		if (KEY->keyDown)
		{
			Stairs* stair = (Stairs*)other;
			int xDestination, yDestination;
			stair->calSimonNewPosMidHeight(xDestination, yDestination);
			SIMON->initGoTo(xDestination, yDestination, 0.2, stair);
			curAnimation = nextAnimation = SA_DOWNSTAIR;
			curFrame = 0;
			onStair = true;
		}
	}
}

void Simon::onAABBCheck(BaseObject * other)
{
}

void Simon::draw()
{
	if (!alive)
		return;

	if (sprite == 0)
		return;

	if (!allowDraw)
		return;

	int xInViewport, yInViewport;
	int widthImg = sprite->animates[curAnimation].frames[curFrame].width;
	updateX = (widthImg / 2) - (width / 2);
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
	int trucQuay = xInViewport + width / 2;

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}

	if ((curAnimation == SA_STAND_ATTACK || curAnimation == SA_RANGE_ATTACK || curAnimation == SA_SITDOWN_ATTACK || curAnimation == SA_UPSTAIR_ATTACK || curAnimation == SA_DOWNSTAIR_ATTACK) && curFrame == 2)
		xInViewport -= updateX;

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);

	if (curAnimation == SA_STAND_ATTACK || curAnimation == SA_JUMP_ATTACK || curAnimation == SA_UPSTAIR_ATTACK || curAnimation == SA_DOWNSTAIR_ATTACK)
		WHIP->draw();

	if (curAnimation == SA_SITDOWN_ATTACK)
		WHIPSITDOWN->draw();

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}
}

void Simon::updateLocation()
{
	if (onStair)
		return;

	if (!alive)
		return;

	if (isCollisionCross && !isCollision)
	{
		if (abs(dx) > abs(dy))
			dy = 0;
		else
			dx = 0;
	}

	if (x + dx < Stage::curStage->left() && dx < 0)
	{
		x = Stage::curStage->left();
		dx = 0;
	}

	if (right() + dx > Stage::curStage->right() && dx > 0)
	{
		x = Stage::curStage->right() - width;
		dx = 0;
	}

	x += dx;
	y += dy;
}

void Simon::changeAction(int newAction)
{
	if (newAction == SA_JUMP && curAnimation == SA_DEATH)
		return;

	if (newAction == SA_DAMAGED && onStair)
		return;

	DrawableObject::changeAction(newAction);

	if (curAnimation != newAction &&  newAction == SA_DEATH)
	{
		if (level == 2)
			GAMESOUND->stop(MUSIC_LEVEL2);
		if (level == 3)
			GAMESOUND->stop(MUSIC_LEVEL3);
		GAMESOUND->play(DEATH);
		curAnimation = newAction;
	}
}

void Simon::initGoTo(float xDestination, float yDestination, float duration, Stairs* stairInterserct)
{
	if (stairInterserct->id / 100 != 0)
		directionStair = (Direction)stairInterserct->directionStair;

	this->xDestination = xDestination;
	this->yDestination = yDestination;

	float deltaX = xDestination - x;
	float deltaY = yDestination - y;

	this->stairInterserct = stairInterserct;

	if (duration == 0)
	{
		vxStair = vx = 0;
		vyStair = vy = 0;
	}
	else
	{
		vxStair = vx = deltaX / duration;
		vyStair = vy = deltaY / duration;
	}

	onGoTo = true;
}

void Simon::goUp(Stairs * stairInterserct)
{
	if (stairInterserct->directionStair != directionStair && stairInterserct->id / 100 != 0)
		return;

	direction = (Direction)directionStair;
	curAnimation = nextAnimation = SA_UPSTAIR;
	if(!KEY->keyDown && !KEY->keyUp)
		curFrame = 0;
	initGoTo(x + directionStair * 8, y - 8, 1, stairInterserct);

}

void Simon::goDown(Stairs * stairInterserct)
{
	if (stairInterserct->directionStair != directionStair && stairInterserct->id / 100 != 0)
		return;

	direction = (Direction)-directionStair;
	curAnimation = nextAnimation = SA_DOWNSTAIR;
	if (!KEY->keyDown && !KEY->keyUp)
		curFrame = 0;
	initGoTo(x - directionStair * 8, y + 8, 1, stairInterserct);

}

void Simon::updateGoTo()
{
	DrawableObject::update();

	//dx = vx == 0 ? 0 : 0.7 * vx / abs(vx);
	//dy = vy == 0 ? 0 : 0.7 * vy / abs(vy);

	if (vx == 0)
		dx = 0;
	else
	{
		if (vx > 0)
			dx = 0.7;
		else
			dx = -0.7;
	}

	if (vy == 0)
		dy = 0;
	else
	{
		if (vy > 0)
			dy = 0.7;
		else
			dy = -0.7;
	}

	if (abs(dx) >= abs(xDestination - x))
	{
		x = xDestination;
		vx = 0;
		dx = 0;
	}

	if (abs(dy) >= abs(yDestination - y))
	{
		y = yDestination;
		vy = 0;
		dy = 0;
	}

	if ((x == xDestination && y == yDestination) || (vx == 0 && vy == 0))
	{
		vx = 0;
		vy = 0;
		dx = 0;
		dy = 0;
		onGoTo = false;
		atDestination();
	}
	x += dx;
	y += dy;
}

void Simon::atDestination()
{
	if (!KEY->keyUp && !KEY->keyDown && !KEY->keyLeft && !KEY->keyRight)
		curFrame = 1;

	if (stairInterserct->id == ST_BOTTOM || stairInterserct->id == ST_LEFT_BOTTOM)
	{
		int xDestination, yDestination;
		stairInterserct->calSimonNewPosMidWidth(xDestination, yDestination);

		if (x == xDestination && y == yDestination && curAnimation != SA_DOWNSTAIR)
			goUp(stairInterserct);
	}

	if (stairInterserct->id == ST_TOP || stairInterserct->id == ST_LEFT_TOP || stairInterserct->id == ST_CHANGE_STAGE)
		if (bottom() == stairInterserct->top())
		{
			onStair = false;
			onGoTo = false;
		}
}

Simon::Simon()
{
	stairInterserct = 0;
	onGoTo = false;
	onStair = false;
	sprite = SPRITEMANAGER->sprites[SPR_SIMON];
	x = 1824;
	y = 706;
	level = 2;
	width = 16;
	height = 30;
	updateX = 0;
	life = 16;
	invisible = false;
	invisibilityPoint = false;
	score = 0;
	collisionType = CT_PLAYER;
	weaponType = WT_DEFAULT;
	doorUpdating = 0;
	numberOfAttacks = 5;
	gameTimeLoop.init(0.01, 100);
	gameTimeLoop.start();
	timePickUpItem.init(0.01, 50);
	timePickUpItem.start();
	timeDeath.init(1, 3);
	timeDeath.start();
	onHit = false;
	stage = 4;
	onPickUpItem = false;
	allowDraw = true;
	timeRangeWeaponAppear.init(0.5, 1);
	numberWeaponAppear = 1;
	numberAppear = 1;
	isDeath = false;
	numberOfAlive = 3;
	onAreaBoss = false;
}

Simon::~Simon()
{
}
