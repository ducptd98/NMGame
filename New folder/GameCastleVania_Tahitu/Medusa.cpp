#include "Medusa.h"
#include "Simon.h"
#include "Medusa_Snake.h"
#include "Map.h"

bool Medusa::isDeath = false;
int Medusa::lifeBoss = 16;

void Medusa::update()
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
			dy = 0;
			return;
		}

		if (timeDamaged->isTerminated())
			damaged = false;
	}

	if (!alive && !Medusa::isDeath)
	{
		Medusa::isDeath = true;
		GAMESOUND->stop(MUSIC_LEVEL2);
		GAMESOUND->play(MUSIC_WIN_BOSS, false);
	}

	if (alive)
	{
		if (timeDelayMove->canCreateFrame())
		{
			MEDUSA_SNAKE->_Add(new Medusa_Snake(x, y, direction));
			isDelay = true;
			timeStopMove->start();
			isMove = false;

			if (!isExit)
			{
				changeAction(1);
				y += 16;
				isExit = true;
				isMove = true;
			}
		}

		if (timeDelayMove->isTerminated() && !isDelay)
		{
			if (count % 2 == 0)
				timeDelayMove->init(1, 1);
			else
				timeDelayMove->init(3, 1);

			timeDelayMove->start();
			count++;
		}

		if (timeStopMove->canCreateFrame())
			isMove = true;

		if (timeStopMove->isTerminated())
			isDelay = false;

		if (x >= SIMON->x)
			direction = Left;
		else
			direction = Right;

		if (isMove)
		{
			vx = direction * 35;
			dx = vx * 0.02;
			dy = vy * 0.02 * sin(angle * PI / 180);
			angle += 5;
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

void Medusa::draw()
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

	MovableObject::draw();

	if (damaged && !timeEffect->isTerminated())
		effect->draw(x + 4, y + 4);
}

void Medusa::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType != CT_GROUND)
		Enemy::onCollision(other, nx, ny);
}

void Medusa::onAABBCheck(BaseObject * other)
{
	if (isExit)
	{
		if ((other == WHIP && WHIP->canAttack) || (other == WHIPSITDOWN && WHIPSITDOWN->canAttack) || other->collisionType == CT_WEAPON)
		{
			if (!damaged)
			{
				if (SIMON->weaponType != WT_HOLY_WATER && SIMON->weaponType != WT_BOOMERANG)
					other->allowDelete = true;

				Medusa::lifeBoss--;
				damaged = true;
				timeDamaged->start();
				timeEffect->start();
				GAMESOUND->play(ENEMY_HIT2, false);
			}

			if (Medusa::lifeBoss <= 0)
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
}

void Medusa::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	Medusa::lifeBoss = 16;
	vy = 30;
	count = 0;
	angle = 0;
	timeStopMove = new GameTimeLoop();
	timeStopMove->init(3, 1);
	timeDelayMove = new GameTimeLoop();
	timeDelayMove->init(5, 1);
	timeDelayMove->start();
	isMove = false;
	isDelay = true;
	isExit = false;
}

Medusa::Medusa()
{
	vy = 30;
	count = 0;
	angle = 0;
	timeStopMove = new GameTimeLoop();
	timeStopMove->init(3, 1);
	timeDelayMove = new GameTimeLoop();
	timeDelayMove->init(5, 1);
	timeDelayMove->start();
	timeDamaged = new GameTimeLoop();
	timeDamaged->init(0.6, 1);
	timeEffect = new GameTimeLoop();
	timeEffect->init(0.2, 1);
	isMove = false;
	isDelay = true;
	isExit = false;
	score = 3000;
}

Medusa::~Medusa()
{
}