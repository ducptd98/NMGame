#include "Skeleton.h"
#include "Simon.h"
#include "GameTimeLoop.h"
#include "Skeleton_Bone.h"
#include "Map.h"

void Skeleton::update()
{
	if (damaged)
	{
		dx = 0;
		gameTimeLoop.canCreateFrame();

		if (gameTimeLoop.isTerminated())
			damaged = false;

		return;
	}

	if (this->bottom() <= CAMERA->top())
		alive = false;

	if (alive)
	{
		if (timeCreateBone->canCreateFrame())
		{
			SKELETON_BONE->_Add(new Skeleton_Bone(x, y, direction, -(rand()%150 + 140)));
			count++;
		}

		if (timeCreateBone->isTerminated())
		{
			if (count % 4 == 0 || count % 5 == 0)
				timeCreateBone->init(0.1, 1);
			else
				timeCreateBone->init(2, 1);

			timeCreateBone->start();
		}

		if (x > SIMON->x)
			direction = Left;
		else
			direction = Right;

		vx = direction * 30;
		vy += ay * TIME;
		dx = vx * 0.02;
		dy = vy * 0.02;
		isOnGround = false;

		if (SIMON->direction != direction && (abs(SIMON->x - x) < 40))
		{
			if ((SIMON->direction == Right && SIMON->x < x) || SIMON->direction == Left && SIMON->x > x)
				isChangeMoving = true;
			else
				isChangeMoving = false;
		}		
		
		if ((SIMON->direction == direction) || abs(SIMON->x - x) > 70)
			isChangeMoving = false;

		if (isChangeMoving)
		{
			if (direction == Left)
			{
				if (abs(SIMON->x - x) <= 70)
					dx = abs(vx*0.02);
				else if (abs(SIMON->x - x) >= 40)
					dx = - abs(vx*0.02);
			}

			if (direction == Right)
			{
				if (abs(SIMON->x - x) <= 70)
					dx = -abs(vx*0.02);
				else if (abs(SIMON->x - x) >= 40)
					dx = abs(vx*0.02);
			}
		}

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

void Skeleton::draw()
{
	Enemy::draw();
}

void Skeleton::onCollision(BaseObject * other, int nx, int ny)
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
				vy = -150;
				isJumping = true;
			}
		}
		else
			isJumping = false;
	}
}

void Skeleton::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	life = 1;
	timeCreateBone = new GameTimeLoop();
	timeCreateBone->init(2, 1);
	timeCreateBone->start();
	count = 0;
	isJumping = false;
	isChangeMoving = false;
}

Skeleton::Skeleton()
{
	score = 400;
	life = 1; 
	damage = 3;
	ay = GRAVITY;
	timeCreateBone = new GameTimeLoop();
	timeCreateBone->init(2, 1);
	timeCreateBone->start();
	count = 0;
	isJumping = false;
	isChangeMoving = false;
}

Skeleton::~Skeleton()
{
}