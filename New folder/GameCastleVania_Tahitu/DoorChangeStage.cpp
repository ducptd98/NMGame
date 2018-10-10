#include "DoorChangeStage.h"
#include "Simon.h"
#include "Stage.h"
#include "Camera.h"
#include "Map.h"

void DoorChangeStage::onAABBCheck(BaseObject * other)
{
	if (other == SIMON && SIMON->bottom() == bottom())
	{
		if (!updating)
			SIMON->setPauseAnimation(true, 0);

		updating = true;
		SIMON->doorUpdating = &updating;
		SIMON->curAnimation = SA_WALK;
		CAMERA->dx = 0;
		SIMON->dx = 0;
		SIMON->dy = 0;
	}
}

void DoorChangeStage::openDoor()
{
	setPauseAnimation(false, 0);
}

void DoorChangeStage::update()
{
	if (!updating)
		return;

	if (SIMON->level == 2)
	{
		switch (doorAction)
		{
		case DA_CAMERA_RUN1:
			CAMERA->x--;
			Map::curMap->xMap++;

			if (CAMERA->xCenter() <= xCenter())
			{
				doorAction = DA_OPEN_DOOR;
				openDoor();
			}
			break;
		case DA_OPEN_DOOR:
			DrawableObject::update();

			if (curFrame == 0 && !pauseAnimation)
			{
				setPauseAnimation(true, sprite->animates[curAnimation].nFrame - 1);
				SIMON->setPauseAnimation(false, 0);
				doorAction = DA_SIMON_RUN;
				SIMON->curAnimation = SA_WALK;

			}
			break;
		case DA_SIMON_RUN:
			SIMON->x--;
			if (SIMON->x < CAMERA->x + CAMERA->width / 4)
			{
				SIMON->changeAction(SA_STAND);
				doorAction = DA_CLOSE_DOOR;
				SIMON->dx = 0;
				curFrame = 0;
				nextAnimation = curAnimation = 1;
				setPauseAnimation(false, 0);
			}
			break;
		case DA_CLOSE_DOOR:
			DrawableObject::update();

			if (curFrame == 0)
			{
				setPauseAnimation(true, sprite->animates[curAnimation].nFrame - 1);
				doorAction = DA_CAMERA_RUN2;
				CAMERA->dx = 0;
				SIMON->dx = 0;
			}
			break;
		case DA_CAMERA_RUN2:
			CAMERA->dx = 0;
			CAMERA->x--;
			Map::curMap->xMap++;
			if (CAMERA->right() <= Stage::curStages->at(Stage::curStage->index + 1)->right())
			{
				CAMERA->x = Stage::curStages->at(Stage::curStage->index + 1)->right() - CAMERA->width;
				Map::curMap->xMap = -CAMERA->x;
				Stage::curStage = Stage::curStages->at(Stage::curStage->index + 1);
				SIMON->stage++;
				updating = false;
			}
			break;
		default:
			break;
		}
	}
	
	if (SIMON->level == 3)
	{
		switch (doorAction)
		{
		case DA_CAMERA_RUN1:
			CAMERA->x++;
			Map::curMap->xMap--;

			if (CAMERA->xCenter() >= xCenter())
			{
				doorAction = DA_OPEN_DOOR;
				openDoor();
			}
			break;
		case DA_OPEN_DOOR:
			DrawableObject::update();

			if (curFrame == 0 && !pauseAnimation)
			{
				setPauseAnimation(true, sprite->animates[curAnimation].nFrame - 1);
				SIMON->setPauseAnimation(false, 0);
				doorAction = DA_SIMON_RUN;
				SIMON->curAnimation = SA_WALK;

			}
			break;
		case DA_SIMON_RUN:
			SIMON->x++;
			if (SIMON->x > CAMERA->right() - CAMERA->width / 4)
			{
				SIMON->changeAction(SA_STAND);
				doorAction = DA_CLOSE_DOOR;
				SIMON->dx = 0;
				curFrame = 0;
				nextAnimation = curAnimation = 1;
				setPauseAnimation(false, 0);
			}
			break;
		case DA_CLOSE_DOOR:
			DrawableObject::update();

			if (curFrame == 0)
			{
				setPauseAnimation(true, sprite->animates[curAnimation].nFrame - 1);
				doorAction = DA_CAMERA_RUN2;
				CAMERA->dx = 0;
				SIMON->dx = 0;
			}
			break;
		case DA_CAMERA_RUN2:
			CAMERA->dx = 0;
			CAMERA->x++;
			Map::curMap->xMap--;
			if (CAMERA->left() >= Stage::curStages->at(Stage::curStage->index + 1)->left())
			{
				CAMERA->x = Stage::curStages->at(Stage::curStage->index + 1)->left();
				Map::curMap->xMap = -CAMERA->x;
				Stage::curStage = Stage::curStages->at(Stage::curStage->index + 1);
				SIMON->stage++;
				updating = false;
			}
			break;
		default:
			break;
		}
	}
}

DoorChangeStage::DoorChangeStage()
{
	collisionType = CT_DOOR;
	setPauseAnimation(true, 0);
	openned = false;
	updating = false;
	doorAction = DA_CAMERA_RUN1;
}

DoorChangeStage::~DoorChangeStage()
{
}
