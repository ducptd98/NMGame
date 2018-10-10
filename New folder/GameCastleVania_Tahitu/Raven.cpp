#include "Raven.h"
#include "Simon.h"
#include "Map.h"

void Raven::update()
{
	if (alive)
	{
		if (abs(SIMON->x - x) < 120 && abs(SIMON->y - y) < 100 && !isBegin)
		{
			timeDelayMove->start();
			isMove = true;
			changeAction(1);
			isBegin = true;
			vx = 50;
		}

		if (timeDelayMove->canCreateFrame() && isBegin)
		{
			isDelay = true;
			timeStopMove->start();
			isMove = false;

			if (!isExist)
			{
				changeAction(1);
				isExist = true;
				isMove = true;
			}
		}

		if (timeDelayMove->isTerminated() && !isDelay)
		{
			if (rand() % 2 == 0)
				timeDelayMove->init(rand()%2 + 0.5, 1);
			else
				timeDelayMove->init(1.0, 1);

			timeDelayMove->start();
		}

		if (timeStopMove->canCreateFrame())
		{
			isMove = true;
			vx = 50;

			if (this->top() > SIMON->bottom())
				vy = -30;
			else
			{
				if (SIMON->top() - this->bottom() > 8)
					vy = 30;
				else
					if (rand() % 2 == 0)
						vy = 0;
					else
						vy = 20;
			}
		}

		if (timeStopMove->isTerminated())
			isDelay = false;

		if (this->left() > SIMON->right())
			direction = Left;
		else if (this->right() < SIMON->left())
			direction = Right;

		if (isMove)
		{
			dx = vx * 0.02 * direction;
			dy = vy * 0.02;
			isOnGround = false;
		}
		else
			vx = dy = dx = 0;

		DrawableObject::update();
	}
}

void Raven::draw()
{
	if (alive)
		MovableObject::draw();
	else
	{
		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_DELETEOBJECT];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 3;
		}

		if (timeDeath.isTerminated())
			return;

		int xInViewport, yInViewport;
		TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
	}
}

void Raven::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType != CT_GROUND)
		Enemy::onCollision(other, nx, ny);
}

void Raven::onAABBCheck(BaseObject * other)
{
	if ((other == WHIP && WHIP->canAttack) || (other == WHIPSITDOWN && WHIPSITDOWN->canAttack) || other->collisionType == CT_WEAPON)
	{
		if (SIMON->weaponType != WT_HOLY_WATER && SIMON->weaponType != WT_BOOMERANG)
			other->allowDelete = true;

		alive = false;
		SIMON->score += score;
		GAMESOUND->play(ENEMY_HIT2, false);
	}

	if (other == SIMON)
	{
		if (!SIMON->onHit && !SIMON->invisible && !SIMON->invisibilityPoint)
		{
			if (SIMON->onStair)
				SIMON->invisible = true;
			else
			{
				SIMON->changeAction(SA_DAMAGED);
				SIMON->curFrame = 0;
			}

			alive = false;
			SIMON->setOnHit(true);
			SIMON->life = SIMON->life - damage;
			SIMON->gameTimeLoop.start();
		}

		if (SIMON->life <= 0 && !SIMON->onHit)
		{
			SIMON->curFrame = 0;
			SIMON->changeAction(SA_DAMAGED);
			SIMON->setOnHit(true);
			SIMON->gameTimeLoop.start();
		}
	}
}

void Raven::restore(BaseObject* obj)
{
	Enemy::restore(obj);

	vy = 20;
	vx = 50;
	timeStopMove = new GameTimeLoop();
	timeStopMove->init(1.5, 1);
	timeDelayMove = new GameTimeLoop();
	timeDelayMove->init(0.2, 1);
	isMove = false;
	isDelay = true;
	isExist = false;
	isBegin = false;
	life = 1;
}

Raven::Raven()
{
	vy = 20;
	vx = 50;
	timeStopMove = new GameTimeLoop();
	timeStopMove->init(0.5, 1);
	timeDelayMove = new GameTimeLoop();
	timeDelayMove->init(0.2, 1);
	isMove = false;
	isDelay = true;
	isExist = false;
	isBegin = false;
	score = 200;
	life = 1;
	damage = 3;
}

Raven::~Raven()
{
}