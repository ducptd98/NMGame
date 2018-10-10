#include "MedusaHead_List.h"
#include "Map.h"

List<MedusaHead_List*>* MedusaHead_List::listMedusaHead_List = 0;
List<MedusaHead_List*>* MedusaHead_List::getListMedusaHead_List()
{
	if (listMedusaHead_List == 0)
		listMedusaHead_List = new List<MedusaHead_List*>();

	return listMedusaHead_List;
}

void MedusaHead_List::update()
{
	if ((x + dx < CAMERA->left() && dx < 0) || (right() + dx > CAMERA->right() && dx > 0))
		allowDelete = true;

	vx = direction * 75;
	dx = vx * 0.02;
	dy = vy * 0.02 * sin(angle * PI / 180);
	angle += 3;
	isOnGround = false;

	DrawableObject::update();
}

void MedusaHead_List::draw()
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

void MedusaHead_List::onAABBCheck(BaseObject * other)
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
		SIMON->score += score;
		GAMESOUND->play(ENEMY_HIT2, false);
	}
}

void MedusaHead_List::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_GROUND)
		return;
}

MedusaHead_List::MedusaHead_List()
{
	sprite = SPRITEMANAGER->sprites[SPR_MEDUSAHEAD];
	vy = 80;
	vx = 70;
	ay = 0;
	width = height = 16;
	angle = 90;
	x = oldX = -(Map::curMap->xMap + width);
	y = SIMON->y + 6;

	if (SIMON->direction != -1)
		x += VIEWPORT_WIDTH;

	if (direction == SIMON->direction)
		direction = (Direction)(-SIMON->direction);

	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	score = 300;
	life = 1;
	damage = 2;
	allowDelete = false;
	isCollisionSIMON = false;
}

MedusaHead_List::~MedusaHead_List()
{
}
