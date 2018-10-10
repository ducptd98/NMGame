#include "HolyWater.h"
#include "MovableObject.h"

List<HolyWater*>* HolyWater::holyWaters = 0;
List<HolyWater*>* HolyWater::getHolyWaters()
{
	if (holyWaters == 0)
		holyWaters = new List<HolyWater*>();
	return holyWaters;
}

void HolyWater::updateVerlocity()
{
	vy += ay * TIME;
	dx = vx * TIME;
	dy = vy * TIME;
}

void HolyWater::update()
{
	isCollisionCross = false;
	isCollision = false;

	if (isCollisonGround)
	{
		if (gameTimeLoop.canCreateFrame())
		{
			switch (curFrame)
			{
			case 1:
				GAMESOUND->play(HOLY_WATER1);
				curFrame = 2;
				break;
			case 2:
				curFrame = 1;
				break;
			default:
				break;
			}
		}

		if (gameTimeLoop.isTerminated())
		{
			isCollisonGround = false;
			curFrame = 0;
			allowDelete = true;
			gameTimeLoop.start();
		}
	}

	vx = 60 * direction;

	updateVerlocity();

	if (isCollisonGround)
	{
		dx = 0;
		dy = 0;
	}
}

void HolyWater::draw()
{
	Weapon::draw();
}

void HolyWater::onAABBCheck(BaseObject * other)
{
	Weapon::onAABBCheck(other);
}

void HolyWater::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_GROUND)
	{
		isCollisonGround = true;

		if (ny != 1)
			curFrame = 2;
	}
	else
		isCollisonGround = false;
}

HolyWater::HolyWater()
{
	sprite = SPRITEMANAGER->sprites[SPR_HOLYWATER];
	getHolyWaters()->_Add(this);
	gameTimeLoop.init(0.4, 7);
	gameTimeLoop.start();
	height = 10;
	isCollisonGround = false;
	vy = -100;
	ay = GRAVITY;
}

HolyWater::~HolyWater()
{
}
