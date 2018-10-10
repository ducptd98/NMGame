#include "BoneTower.h"
#include "Simon.h"
#include "GameTimeLoop.h"
#include "BoneTower_Bullet.h"

void BoneTower::update()
{
	if (damaged)
	{
		gameTimeLoop.canCreateFrame();

		if (gameTimeLoop.isTerminated())
			damaged = false;

		return;
	}

	if (alive)
	{
		if (x >= SIMON->x)
			direction = Left;
		else
			direction = Right;

		if (gameTimeLoopBullet->canCreateFrame())
		{
			if (countBullet % 2 == 0)
			{
				isChangeColor = true;
				timeChangeColor->start();
			}

			BONETOWER_BULLET->_Add(new BoneTower_Bullet(this->x, this->y, this->direction));

			countBullet++;
		}

		if (isChangeColor && timeChangeColor->canCreateFrame())
		{
			changeAction(1);
		}

		if (timeChangeColor->isTerminated())
		{
			isChangeColor = false;
			changeAction(0);
		}

		if (gameTimeLoopBullet->isTerminated())
		{
			if (countBullet % 2 != 0)
			{
				gameTimeLoopBullet->init(0.7, 1);
				gameTimeLoopBullet->start();
			}
			else
			{
				gameTimeLoopBullet->init(3, 1);
				gameTimeLoopBullet->start();
			}
		}
	}

	MovableObject::update();
}

void BoneTower::draw()
{
	Enemy::draw();
}

void BoneTower::onCollision(BaseObject * other, int nx, int ny)
{
	Enemy::onCollision(other, nx, ny);
}

void BoneTower::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	life = 6;
}

BoneTower::BoneTower()
{
	vy = 0;
	ay = 0;
	score = 400;
	life = 6; // weak: 8,    strong: 6
	gameTimeLoopBullet = new GameTimeLoop();
	gameTimeLoopBullet->init(0.7, 1);
	gameTimeLoopBullet->start();

	timeChangeColor = new GameTimeLoop();
	timeChangeColor->init(0.1, 1);
	isChangeColor = false;
}

BoneTower::~BoneTower()
{
}