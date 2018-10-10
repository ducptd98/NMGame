#include "Fleamen.h"
#include "Simon.h"

void Fleamen::update()
{
	if (SIMON->x >= x && !SIMON->invisible && vy == 0)
		direction = Right;

	if (SIMON->x <= x && !SIMON->invisible && vy == 0)
		direction = Left;

	if (vy == 0)
		vy = -60;

	if ((abs(this->bottom() - SIMON->bottom()) <= 8) && (SIMON->direction != direction && abs(SIMON->x - x) <= 32 && abs(SIMON->x - x) >= 30) &&
		((SIMON->direction == Right && SIMON->x < x) || (SIMON->direction == Left && SIMON->x > x)))
		vy = -200;

	Enemy::update();

	dx = direction * 65 * TIME;
}

void Fleamen::draw()
{
	Enemy::draw();
}

void Fleamen::onCollision(BaseObject * other, int nx, int ny)
{
	Enemy::onCollision(other, nx, ny);

	if (other->collisionType == CT_GROUND && nx != 0)
		direction = (Direction)nx;

	if (other->collisionType == CT_GROUND)
	{
		if (x + 16 >= other->right() || x <= other->left())
		{
			if (!isJumping)
			{
				isJumping = true;
				vy = -200;
			}
		}
	}
}

void Fleamen::restore(BaseObject * obj)
{
	Enemy::restore(obj);

	score = 500;
	life = 1;
	damage = 3;
	isJumping = false;
}

Fleamen::Fleamen()
{
	score = 500;
	life = 1;
	damage = 3;
	ay = 400;
	isJumping = false;
}

Fleamen::~Fleamen()
{
}