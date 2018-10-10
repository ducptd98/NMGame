#include "MummyMan_Bandage.h"
#include "Map.h"

List<MummyMan_Bandage*>* MummyMan_Bandage::listMummyMan_Bandage = 0;
List<MummyMan_Bandage*>* MummyMan_Bandage::getListMummyMan_Bandage()
{
	if (listMummyMan_Bandage == 0)
		listMummyMan_Bandage = new List<MummyMan_Bandage*>();

	return listMummyMan_Bandage;
}

void MummyMan_Bandage::update()
{
	if ((x + dx < CAMERA->left() && dx < 0) || (right() + dx > CAMERA->right() && dx > 0))
		allowDelete = true;

	vx = direction * 60;
	dx = vx * 0.02;
	dy = vy * 0.02 * sin(angle * PI / 180);
	angle += 5;

	Weapon::update();
}

void MummyMan_Bandage::draw()
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

void MummyMan_Bandage::onAABBCheck(BaseObject * other)
{
	if (other == SIMON && !isCollisionSIMON && !SIMON->onHit && !SIMON->invisible)
	{
		isCollisionSIMON = true;
		SIMON->life -= damage;
		SIMON->changeAction(SA_DAMAGED);
		SIMON->setOnHit(true);
		SIMON->gameTimeLoop.start();
	}

	if ((other == WHIP && WHIP->canAttack) || (other == WHIPSITDOWN && WHIPSITDOWN->canAttack) || other->collisionType == CT_WEAPON)
		alive = false;
}

MummyMan_Bandage::MummyMan_Bandage(int xMummyMan, int yMummyMan, Direction directionMummyMan)
{
	sprite = SPRITEMANAGER->sprites[SPR_MUMMYMAN_BANDAGE];
	direction = directionMummyMan;
	width = 7;
	height = 6;
	angle = 90;
	x = xMummyMan - 4;
	y = yMummyMan + 20;

	if (direction == Right)
		x += 10;

	vy = 70;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	allowDelete = false;
	isCollisionSIMON = false;
	damage = 2;
	timeDeath.init(0.2, 10);
	timeDeath.start();
}

MummyMan_Bandage::MummyMan_Bandage()
{
}


MummyMan_Bandage::~MummyMan_Bandage()
{
}
