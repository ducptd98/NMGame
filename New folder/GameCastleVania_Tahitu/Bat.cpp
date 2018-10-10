#include "Bat.h"
#include "Simon.h"
#include "Map.h"

void Bat::update()
{
	if (damaged)
	{
		if (gameTimeLoop.canCreateFrame())
			return;

		if (gameTimeLoop.isTerminated())
			damaged = false;

		return;
	}

	if (x < CAMERA->left() - 20 || x > CAMERA->right() + 20)
		alive = false;

	if (alive && abs(x - SIMON->x) < 100 && (abs(y - SIMON->y) < 40) && !isFly) 
	{
		ay = 150;
		oldYSimon = SIMON->y;
		isFly = true;
		changeAction(1);
	}

	if (alive && isFly)
	{
		vx = direction * 80;
		
      	if (oldYSimon - y < 0)
		{
			ay = 0;
			vy = 0;
			dy = 0;
		}
	}

	MovableObject::update();
}

void Bat::draw()
{
	Enemy::draw();
}

void Bat::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType != CT_GROUND)
		Enemy::onCollision(other, nx, ny);
}

void Bat::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	life = 1;
	vx = 0;
	vy = 0;
	ay = 0;
	oldYSimon = 0;
	isFly = false;
}

Bat::Bat()
{
	vx = 0;
	vy = 0;
	ay = 0;
	oldYSimon = 0;
	isFly = false;
	score = 200;
	life = 1;
	damage = 2;
}

Bat::~Bat()
{
}
