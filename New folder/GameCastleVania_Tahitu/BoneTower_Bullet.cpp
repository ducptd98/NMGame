#include "BoneTower_Bullet.h"
#include "Map.h"

List<BoneTower_Bullet*>* BoneTower_Bullet::listBoneTower_Bullet = 0;
List<BoneTower_Bullet*>* BoneTower_Bullet::getListBoneTower_Bullet()
{
	if (listBoneTower_Bullet == 0)
		listBoneTower_Bullet = new List<BoneTower_Bullet*>();

	return listBoneTower_Bullet;
}

void BoneTower_Bullet::update()
{
	if ((x + dx < CAMERA->left() && dx < 0) || (right() + dx > CAMERA->right() && dx > 0))
		allowDelete = true;

	vx = direction * 80;
	dx = vx * 0.02;

	Weapon::update();
}

void BoneTower_Bullet::draw()
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
		{
			allowDelete = true;
			return;
		}

		int xInViewport, yInViewport;
		TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
	}

	Weapon::draw();
}

void BoneTower_Bullet::onAABBCheck(BaseObject * other)
{
	if (other == SIMON && !isCollisionSIMON && !SIMON->onHit && !SIMON->invisible)
	{
		isCollisionSIMON = true;
		SIMON->life -= 2;
		SIMON->changeAction(SA_DAMAGED);
		SIMON->setOnHit(true);
		SIMON->gameTimeLoop.start();
	}

	if ((other == WHIP && WHIP->canAttack) || (other == WHIPSITDOWN && WHIPSITDOWN->canAttack) || other->collisionType == CT_WEAPON)
	{
		alive = false;
		GAMESOUND->play(ENEMY_HIT2, false);
	}
}

BoneTower_Bullet::BoneTower_Bullet(int xBoneTower, int yBoneTower, Direction directionBoneTower)
{
	sprite = SPRITEMANAGER->sprites[SPR_BONETOWER_BULLET];
	direction = directionBoneTower;
	width = 7;
	height = 6;
	x = xBoneTower - 4;
	y = yBoneTower + 7;

	if (direction == Right)
		x += 10;

	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	allowDelete = false;
	isCollisionSIMON = false;
	timeDeath.init(0.2, 10);
	timeDeath.start();
}

BoneTower_Bullet::BoneTower_Bullet()
{
}

BoneTower_Bullet::~BoneTower_Bullet()
{
}
