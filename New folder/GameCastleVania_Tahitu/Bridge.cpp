#include "Bridge.h"
#include "Simon.h"

void Bridge::update()
{
	vx = direction * 40;
	MovableObject::update();
}

void Bridge::onCollision(BaseObject * other, int nx, int ny)
{
	if (ny == -1 && other == SIMON)
		SIMON->dx += dx;

	if (other->collisionType == CT_GROUND && nx != 0)
		direction = (Direction)nx;

	MovableObject::onCollision(other, nx, ny);
}

Bridge::Bridge()
{
	collisionType = CT_BRIDGE;
	ay = 0;
}

Bridge::~Bridge()
{
}
