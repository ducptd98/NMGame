#include "Skeleton_Bone.h"
#include "Map.h"

List<Skeleton_Bone*>* Skeleton_Bone::listSkeleton_Bone = 0;
List<Skeleton_Bone*>* Skeleton_Bone::getListSkeleton_Bone()
{
	if (listSkeleton_Bone == 0)
		listSkeleton_Bone = new List<Skeleton_Bone*>();

	return listSkeleton_Bone;
}

void Skeleton_Bone::update()
{
	if ((x + dx < CAMERA->left() && dx < 0) || (right() + dx > CAMERA->right() && dx > 0) || 
		(y + dy > CAMERA->bottom()) || (y < CAMERA->top()))
		allowDelete = true;

	vx = direction * 70;
	vy += ay * TIME;
	dx = vx * TIME;
	dy = vy * TIME;
	Weapon::update();
}

void Skeleton_Bone::draw()
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

void Skeleton_Bone::onAABBCheck(BaseObject * other)
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
	{
		alive = false;
		GAMESOUND->play(ENEMY_HIT2, false);
	}
}

Skeleton_Bone::Skeleton_Bone(int xSkeleton, int ySkeleton, Direction directionSkeleton, int vy)
{
	sprite = SPRITEMANAGER->sprites[SPR_SKELETON_BONE];
	direction = directionSkeleton;
	width = 15;
	height = 16;
	x = xSkeleton + 8;
	y = ySkeleton + 16;
	this->vy = vy;
	ay = 400;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	allowDelete = false;
	isCollisionSIMON = false;
	damage = 2;
	timeDeath.init(0.2, 10);
	timeDeath.start();
}

Skeleton_Bone::Skeleton_Bone()
{
}

Skeleton_Bone::~Skeleton_Bone()
{
}
