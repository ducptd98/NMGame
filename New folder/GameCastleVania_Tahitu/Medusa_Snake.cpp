#include "Medusa_Snake.h"
#include "Map.h"

List<Medusa_Snake*>* Medusa_Snake::listMedusa_Snake = 0;
List<Medusa_Snake*>* Medusa_Snake::getListMedusa_Snake()
{
	if (listMedusa_Snake == 0)
		listMedusa_Snake = new List<Medusa_Snake*>();

	return listMedusa_Snake;
}

void Medusa_Snake::update()
{
	if ((x + dx < CAMERA->left() && dx < 0) || (right() + dx > CAMERA->right() && dx > 0)
		|| (y > CAMERA->bottom()) || (y + dy < CAMERA->top()))
		allowDelete = true;

	if (alive)
		vx = direction * 50;

	MovableObject::update();
}

void Medusa_Snake::draw()
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

	MovableObject::draw();
}

void Medusa_Snake::onAABBCheck(BaseObject * other)
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

void Medusa_Snake::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_GROUND)
	{
		if (ny != 1)
			COLLISION->preventMove(this, other);

		if (nx != 0)
			y += 0.001f;
	}
}

Medusa_Snake::Medusa_Snake(int xMedusa, int yMedusa, Direction directionMedusa)
{
	sprite = SPRITEMANAGER->sprites[SPR_MEDUSA_SNAKE];
	direction = directionMedusa;
	width = 17;
	height = 10;
	x = xMedusa + 16;
	y = yMedusa;
	ay = 100;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	allowDelete = false;
	isCollisionSIMON = false;
}

Medusa_Snake::Medusa_Snake()
{
}

Medusa_Snake::~Medusa_Snake()
{
}
