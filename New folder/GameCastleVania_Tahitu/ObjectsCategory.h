#pragma once
#include "Enemy.h"
#include "List.h"
#include "Stairs.h"

//add
class ObjectsCategory
{
public:
	List<Enemy*> enemies;
	List<BaseObject*> grounds;
	List<BaseObject*> preventMoveCameras;
	List<Stairs*> stairs;
	List<BaseObject*> allObjects;
	List<BaseObject*> items;
	List<BaseObject*> bridges;
	List<BaseObject*> bricks;

	void add(BaseObject* object);
	void remove(BaseObject* object);

	ObjectsCategory(void);
	~ObjectsCategory(void);
};

