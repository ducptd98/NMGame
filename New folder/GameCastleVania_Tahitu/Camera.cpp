#include "Camera.h"
#include "Stage.h"

Camera* Camera::instance = 0;
Camera* Camera::getInstance()
{
	if (instance == 0)
		instance = new Camera();
	return instance;
}

void Camera::onCollision(BaseObject* other, int nx, int ny)
{
	if (other->collisionType == CT_PREVENTMOVECAMERA)
		COLLISION->preventMove(this, other);
}

void Camera::update()
{
	if ((SIMON->x + SIMON->dx < xCenter() && SIMON->dx < 0) || (SIMON->x + SIMON->dx > xCenter() && SIMON->dx > 0))
		dx = SIMON->dx;
	else
		dx = 0;

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
}

Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}
