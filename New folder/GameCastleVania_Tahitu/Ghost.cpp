#include "Ghost.h"
#include "Simon.h"

void Ghost::update()
{
	if (x - SIMON->x > 80)
		isExist = true;

	if (!isExist)
		return;

	if (damaged)
	{
		dx = 0;
		dy = 0;
		gameTimeLoop.canCreateFrame();

		if (gameTimeLoop.isTerminated())
			damaged = false;

		return;
	}

	if (abs(x - SIMON->x) > 16)
	{
		if (x > SIMON->x)
			direction = Left;
		else
			direction = Right;

		if (oldY - y < 3)
			vy = -60;

		ay = GRAVITY;
		vx = direction * 40;
	}
	else 
	{
		if (SIMON->y - y  > 0)
			ay = 100;
		else
			ay = -10;

		vx = direction * 30;
	}

	MovableObject::update();
}

void Ghost::draw()
{
	if (isExist)
		Enemy::draw();
}

void Ghost::onCollision(BaseObject * other, int nx, int ny)
{
	if (!isExist)
		return;

	if (other->collisionType != CT_GROUND)
		Enemy::onCollision(other, nx, ny);
}

void Ghost::onAABBCheck(BaseObject * other)
{
	if (!isExist)
		return;

	Enemy::onAABBCheck(other);
}

void Ghost::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	isExist = false;
	life = 3;
}

Ghost::Ghost()
{
	isExist = false;
	score = 300;
	life = 3; // weak: 3,    strong: 2
}


Ghost::~Ghost()
{
}
