#include "Enemy.h"
#include "Simon.h"
#include "TileMap.h"
#include "Boomerang.h"
#include "HolyWater.h"

void Enemy::update()
{
	if (damaged)
	{
		dx = 0;
		gameTimeLoop.canCreateFrame();

		if (gameTimeLoop.isTerminated())
			damaged = false;

		return;
	}

	if (alive)
		vx = direction * ENEMY_VX_GO;

	MovableObject::update();
}

void Enemy::draw()
{
	if (!alive)
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

	MovableObject::draw();

	if (damaged)
		effect->draw(x + 4, y + 4);
}

void Enemy::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
}

void Enemy::onAABBCheck(BaseObject * other)
{
	if ((other == WHIP && WHIP->canAttack) || (other == WHIPSITDOWN && WHIPSITDOWN->canAttack) || other->collisionType == CT_WEAPON)
	{
		if (!damaged)
		{
			if (SIMON->weaponType != WT_HOLY_WATER && SIMON->weaponType != WT_BOOMERANG)
				other->allowDelete = true;

			life--;
			damaged = true;
			gameTimeLoop.start();
			GAMESOUND->play(ENEMY_HIT2, false);
		}

		if (life <= 0)
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

void Enemy::restore(BaseObject * obj)
{
	DrawableObject::restore(obj);
	timeDeath.start();
}

Enemy::Enemy(void)
{
	effect = new EffectAttack();
	collisionType = CT_ENEMY;
	life = 1;
	damage = 2;
	score = 400;
	damaged = false;
	gameTimeLoop.init(0.35, 1);
	gameTimeLoop.start();
	timeDeath.init(0.2, 10);
	timeDeath.start();
}

Enemy::~Enemy(void)
{
}
