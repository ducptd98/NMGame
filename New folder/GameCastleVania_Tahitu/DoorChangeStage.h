#pragma once
#include "DrawableObject.h"

enum DOOR_ACTION
{
	DA_CAMERA_RUN1,
	DA_OPEN_DOOR,
	DA_SIMON_RUN,
	DA_CLOSE_DOOR,
	DA_CAMERA_RUN2
};

class DoorChangeStage : public DrawableObject
{
public:
	bool updating;
	bool openned;
	DOOR_ACTION doorAction;

	void onAABBCheck(BaseObject* other);
	void openDoor();
	void update();

	DoorChangeStage();
	~DoorChangeStage();
};

