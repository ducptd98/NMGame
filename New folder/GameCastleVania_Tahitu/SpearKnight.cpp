#include "SpearKnight.h"
#include "Simon.h"

void SpearKnight::update()
{
	if (SIMON->top() < bottom() && SIMON->bottom() > top() && SIMON->x >= x && !SIMON->invisible && changeDirection)
		direction = Right;

	if (SIMON->top() < bottom() && SIMON->bottom() > top() && SIMON->x <= x && !SIMON->invisible && changeDirection)
		direction = Left;

	Enemy::update();
}

void SpearKnight::draw()
{
	Enemy::draw();
}

void SpearKnight::onCollision(BaseObject * other, int nx, int ny)
{
	Enemy::onCollision(other, nx, ny);

	if (other->collisionType == CT_GROUND && nx != 0)
		direction = (Direction)nx;

	if (right() >= other->right() && nx == 0 && other->collisionType == CT_GROUND)
	{
		changeDirection = false;
		direction = Left;
	}

	if (other->collisionType == CT_GROUND && right() <= other->right() - 16 && left() >= other->left() + 16 && nx == 0)
		changeDirection = true;

	if (left() <= other->left() && nx == 0)
	{
		direction = Right;
		changeDirection = false;
	}
}

void SpearKnight::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	life = 2;
}

SpearKnight::SpearKnight()
{
	changeDirection = true;
	score = 400;
	life = 2;
}

SpearKnight::~SpearKnight()
{
}