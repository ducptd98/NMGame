#include "MummyMan.h"
#include "Simon.h"
#include "GameTimeLoop.h"
#include "MummyMan_Bandage.h"
#include "Map.h"
#include "Medusa.h"

int MummyMan::Boss = 32;

MummyMan* MummyMan::Boss1 = 0;
MummyMan* MummyMan::Boss2 = 0;

void MummyMan::update()
{
	if (!SIMON->onAreaBoss)
		return;

	if (damaged)
	{
		timeEffect->canCreateFrame();
		timeDamaged->canCreateFrame();
		if (!timeEffect->isTerminated())
		{
			dx = 0;
			return;
		}

		if (timeDamaged->isTerminated())
			damaged = false;
	}

	if (!Boss1->alive && !Boss2->alive && !Medusa::isDeath)
	{ 
		GAMESOUND->stop(MUSIC_LEVEL3);
		GAMESOUND->play(MUSIC_WIN_BOSS, false);
		Medusa::isDeath = true;
	}

	if (alive)
	{
		if (timeDelayMove->canCreateFrame())
		{
			if (x > SIMON->x)
				direction = Left;
			else
				direction = Right;

			MUMMYMAN_BANDAGE->_Add(new MummyMan_Bandage(x, y, direction));
			isDelay = true;
			timeStopMove->start();
			isMove = false;

			changeAction(1);
			isInvisible = true;
		}

		if (timeDelayMove->isTerminated() && !isDelay)
		{
			timeDelayMove->init(rand() % 5 + 1, 1);

			changeAction(0);
			timeDelayMove->start();
			isInvisible = false;
			isDraw = 1;
		}

		if (timeStopMove->canCreateFrame())
			isMove = true;

		if (timeStopMove->isTerminated())
			isDelay = false;

		if (direction != SIMON->direction 
			&& ((abs(left() - SIMON->right()) <= 16 && direction == Left) 
				|| (abs(right() - SIMON->left()) <= 16 && direction == Right)))
		{
			switch (direction)
			{
			case Left:
				direction = Right;
				break;
			case Right:
				direction = Left;
				break;
			default:
				break;
			}
		}
		else if (direction != SIMON->direction 
			&& ((abs(left() - SIMON->right()) > 16 && direction == Right && x > SIMON->x) 
				|| (abs(right() - SIMON->left()) > 16 && direction == Left && x < SIMON->x)))
		{
			switch (direction)
			{
			case Left:
				direction = Right;
				break;
			case Right:
				direction = Left;
				break;
			default:
				break;
			}
		}
		else if (direction == SIMON->direction 
			&& ((direction == Left && (abs(SIMON->left() - right()) > 48 && SIMON->x > x))
			|| (direction == Right && (abs(SIMON->right() - left()) > 48 && SIMON->x < x))))
		{
			switch (direction)
			{
			case Left:
				direction = Right;
				break;
			case Right:
				direction = Left;
				break;
			default:
				break;
			}
		}

		if (isMove)
		{
			vx = direction * 30;
			vy = 60;
			dx = vx * 0.02;
			dy = vy * 0.02;
			isOnGround = false;
		}
		else
			vx = dy = dx = 0;

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

		DrawableObject::update();
	}
}

void MummyMan::draw()
{
	if (!alive)
	{
		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_KILL_BOSS];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 3;
		}

		if (timeDeath.isTerminated())
			return;

		int xInViewport, yInViewport;
		TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
	}

	if (isInvisible)
		isDraw = -isDraw;

	if (isDraw == 1)
		MovableObject::draw();

	if (damaged && !timeEffect->isTerminated())
		effect->draw(x + 4, y + 4);
}

void MummyMan::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_GROUND && ny == -1)
		COLLISION->preventMove(this, other);
}

void MummyMan::onAABBCheck(BaseObject * other)
{
	if ((other == WHIP && WHIP->canAttack) ||( other == WHIPSITDOWN && WHIPSITDOWN->canAttack) || other->collisionType == CT_WEAPON)
	{
		if (!damaged)
		{
			if (SIMON->weaponType != WT_HOLY_WATER && SIMON->weaponType != WT_BOOMERANG)
				other->allowDelete = true;

			health--;
			Boss = Boss1->health + Boss2->health;
			Medusa::lifeBoss = Boss / 2;
			damaged = true;
			timeDamaged->start();
			timeEffect->start();
			GAMESOUND->play(ENEMY_HIT2, false);
		}

		if (health <= 0)
		{
			alive = false;
			SIMON->score += score;
		}
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

void MummyMan::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	Medusa::lifeBoss = 16;
	timeStopMove = new GameTimeLoop();
	timeStopMove->init(1, 1);
	timeDelayMove = new GameTimeLoop();
	timeDelayMove->init(2, 1);
	timeDelayMove->start();
	isMove = true;
	isDelay = false;
	isDraw = 1;
	isInvisible = false;
	health = 16;
}

MummyMan::MummyMan()
{
	score = 400;
	timeStopMove = new GameTimeLoop();
	timeStopMove->init(1, 1);
	timeDelayMove = new GameTimeLoop();
	timeDelayMove->init(1.5, 1);
	timeDelayMove->start();
	timeDamaged = new GameTimeLoop();
	timeDamaged->init(0.6, 1);
	timeEffect = new GameTimeLoop();
	timeEffect->init(0.2, 1);
	isMove = true;
	isDelay = false;
	isDraw = 1;
	isInvisible = false;
	health = 16;
	static int curBoss = 0;

	if (curBoss == 0)
		Boss1 = this;
	else
		Boss2 = this;

	curBoss++;
}

MummyMan::~MummyMan()
{
}