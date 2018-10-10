#include "ObjectsCategory.h"

//add
void ObjectsCategory::add(BaseObject* object)
{
	switch (object->collisionType)
	{
	case CT_ENEMY:
		enemies._Add((Enemy*)object);
		break;
	case CT_GROUND:
		grounds._Add(object);
		break;
	case CT_PREVENTMOVECAMERA:
		preventMoveCameras._Add(object);
		break;
	case CT_STAIRS:
		stairs._Add((Stairs*)object);
		break;
	case CT_DOOR:
	case CT_ITEM:
		items._Add(object);
		break;
	case CT_BRIDGE:
		bridges._Add(object);
		break;
	case CT_BRICK:
		bricks._Add(object);
		break;
	default:
		break;
	}

	allObjects._Add(object);
}

void ObjectsCategory::remove(BaseObject* object)
{
	switch (object->collisionType)
	{
	case CT_ENEMY:
		enemies._Remove((Enemy*)object);
		break;
	case CT_GROUND:
		grounds._Remove(object);
		break;
	case CT_PREVENTMOVECAMERA:
		preventMoveCameras._Remove(object);
		break;
	case CT_STAIRS:
		stairs._Remove((Stairs*)object);
		break;
	case CT_DOOR:
	case CT_ITEM:
		items._Remove(object);
		break;
	case CT_BRIDGE:
		bridges._Remove(object);
		break;
	case CT_BRICK:
		bricks._Remove(object);
		break;
	default:
		break;
	}

	allObjects._Remove(object);
}

ObjectsCategory::ObjectsCategory(void)
{
}

ObjectsCategory::~ObjectsCategory(void)
{
}
