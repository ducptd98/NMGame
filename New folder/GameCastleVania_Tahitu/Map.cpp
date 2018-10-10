#include "Map.h"
#include "Simon.h"
#include "Boomerang.h"
#include "Daggers.h"
#include "HolyWater.h"
#include "GameState.h"
#include "Bridge.h"
#include "MedusaHead.h"
#include "BoneTower_Bullet.h"
#include "Medusa_Snake.h"
#include "MummyMan_Bandage.h"
#include "MedusaHead_List.h"
#include "Skeleton_Bone.h"
#include "ThrowingAxe.h"

void Map::init(const char* tileMatrixPath, const char* tileSheetPath, const char* objectsPath, const char* quadtreePath)
{
	TileMap::init(tileMatrixPath, tileSheetPath, objectsPath);
	quadtree.init(quadtreePath, objects);
}

void Map::initStage(const char * stageInfoPath)
{
	fstream fs(stageInfoPath);
	int nStage;
	fs >> nStage;

	for (int i = 0; i < nStage; i++)
		stages._Add(new Stage(fs, i));

	Stage::curStages = &stages;

	if (Stage::curStage == NULL)
		Stage::curStage = stages[0];
}

void Map::restoreAllObject()
{
	for (int i = 0; i < nObjects; i++)
		if (objects[i]->id >= 0)
		{
			DrawableObject* drawableObject = (DrawableObject*)objects[i];
			drawableObject->restore(objects[i]);
		}
}

void Map::update()
{
	if (GameState::curState == PAUSE)
	{
		SIMON->update();
		return;
	}

	CAMERA->update();
	quadtree.update();

	List<BaseObject*>& groundsObject = CAMERA->objectsInCamera.grounds;
	List<Enemy*>& enemiesObject = CAMERA->objectsInCamera.enemies;
	List<BaseObject*>& preventMoveCamerasObject = CAMERA->objectsInCamera.preventMoveCameras;
	List<Stairs*>& stairsObject = CAMERA->objectsInCamera.stairs;
	List<BaseObject*>& itemsObject = CAMERA->objectsInCamera.items;
	List<BaseObject*>& bridgesObject = CAMERA->objectsInCamera.bridges;
	List<BaseObject*>& bricksObject = CAMERA->objectsInCamera.bricks;

	SIMON->update();
	Stage::curStage->update();

	for (int i = 0; i < bridgesObject.size(); i++)
	{
		bridgesObject[i]->update();
		COLLISION->checkCollision(SIMON, bridgesObject[i]);

		for (int j = 0; j < groundsObject.size(); j++)
			COLLISION->checkCollision(bridgesObject[i], groundsObject[j]);

		bridgesObject[i]->updateLocation();
	}

	updateWeapon();

	for (int i = 0; i < itemsObject.size(); i++)
	{
		BaseObject* item = itemsObject[i];
		item->update();

		for (int j = 0; j < groundsObject.size(); j++)
			COLLISION->checkCollision(item, groundsObject[j]);

		for (int j = 0; j < Boomerang::getBoomerangs()->Count; j++)
			COLLISION->checkCollision(Boomerang::getBoomerangs()->at(j), item);

		for (int j = 0; j < Daggers::getDaggers()->Count; j++)
			COLLISION->checkCollision(Daggers::getDaggers()->at(j), item);

		for (int j = 0; j < HolyWater::getHolyWaters()->Count; j++)
			COLLISION->checkCollision(HolyWater::getHolyWaters()->at(j), item);

		for (int j = 0; j < ThrowingAxe::getThrowingAxes()->Count; j++)
			COLLISION->checkCollision(ThrowingAxe::getThrowingAxes()->at(j), item);

		COLLISION->checkCollision(SIMON, item);
		COLLISION->checkCollision(WHIP, item);

		item->updateLocation();
	}

	for (int i = 0; i < enemiesObject.size(); i++)
		enemiesObject[i]->update();

	//MEDUSAHEADS
	for (int i = 0; i < MEDUSAHEADS->size(); i++)
		MEDUSAHEADS->at(i)->update();

	//BONETOWER_BULLET
	for (int i = 0; i < BONETOWER_BULLET->size(); i++)
		BONETOWER_BULLET->at(i)->update();

	//MEDUSA_SNAKE
	for (int i = 0; i < MEDUSA_SNAKE->size(); i++)
		MEDUSA_SNAKE->at(i)->update();

	//MUMMYMAN_BANDAGE
	for (int i = 0; i < MUMMYMAN_BANDAGE->size(); i++)
		MUMMYMAN_BANDAGE->at(i)->update();

	//SKELETON_BONE
	for (int i = 0; i < SKELETON_BONE->size(); i++)
		SKELETON_BONE->at(i)->update();

	for (int i = 0; i < groundsObject.size(); i++)
	{
		COLLISION->checkCollision(SIMON, groundsObject[i]);

		for (int j = 0; j < enemiesObject.size(); j++)
			COLLISION->checkCollision(enemiesObject[j], groundsObject[i]);

		//MEDUSA_SNAKE
		for (int j = 0; j < MEDUSA_SNAKE->size(); j++)
			COLLISION->checkCollision(MEDUSA_SNAKE->at(j), groundsObject[i]);

		for (int j = 0; j < HolyWater::getHolyWaters()->Count; j++)
			COLLISION->checkCollision(HolyWater::getHolyWaters()->at(j), groundsObject[i]);
	}

	for (int i = 0; i < bricksObject.size(); i++)
	{
		COLLISION->checkCollision(SIMON, bricksObject[i]);
		COLLISION->checkCollision(WHIPSITDOWN, bricksObject[i]);
		COLLISION->checkCollision(WHIP, bricksObject[i]);

		for (int j = 0; j < groundsObject.size(); j++)
			COLLISION->checkCollision(bricksObject[i], groundsObject[j]);

		for (int j = 0; j < Boomerang::getBoomerangs()->Count; j++)
			COLLISION->checkCollision(Boomerang::getBoomerangs()->at(j), bricksObject[i]);

		for (int j = 0; j < Daggers::getDaggers()->Count; j++)
			COLLISION->checkCollision(Daggers::getDaggers()->at(j), bricksObject[i]);

		for (int j = 0; j < HolyWater::getHolyWaters()->Count; j++)
			COLLISION->checkCollision(HolyWater::getHolyWaters()->at(j), bricksObject[i]);

		for (int j = 0; j < ThrowingAxe::getThrowingAxes()->Count; j++)
			COLLISION->checkCollision(ThrowingAxe::getThrowingAxes()->at(j), bricksObject[i]);

		bricksObject[i]->updateLocation();
	}

	for (int i = 0; i < enemiesObject.size(); i++)
	{
		if (enemiesObject.at(i)->id == 5)
			continue;

		COLLISION->checkCollision(WHIP, enemiesObject[i]);
		COLLISION->checkCollision(WHIPSITDOWN, enemiesObject[i]);
		COLLISION->checkCollision(SIMON, enemiesObject[i]);

		for (int j = 0; j < Boomerang::getBoomerangs()->Count; j++)
			COLLISION->checkCollision(Boomerang::getBoomerangs()->at(j), enemiesObject[i]);

		for (int j = 0; j < Daggers::getDaggers()->Count; j++)
			COLLISION->checkCollision(Daggers::getDaggers()->at(j), enemiesObject[i]);

		for (int j = 0; j < HolyWater::getHolyWaters()->Count; j++)
			COLLISION->checkCollision(HolyWater::getHolyWaters()->at(j), enemiesObject[i]);

		for (int j = 0; j < ThrowingAxe::getThrowingAxes()->Count; j++)
			COLLISION->checkCollision(ThrowingAxe::getThrowingAxes()->at(j), enemiesObject[i]);
	}

	//MEDUSAHEADS
	for (int i = 0; i < MEDUSAHEADS->size(); i++)
	{
		COLLISION->checkCollision(WHIP, MEDUSAHEADS->at(i));
		COLLISION->checkCollision(WHIPSITDOWN, MEDUSAHEADS->at(i));
		COLLISION->checkCollision(SIMON, MEDUSAHEADS->at(i));

		for (int j = 0; j < Boomerang::getBoomerangs()->Count; j++)
			COLLISION->checkCollision(Boomerang::getBoomerangs()->at(j), enemiesObject[i]);

		for (int j = 0; j < Daggers::getDaggers()->Count; j++)
			COLLISION->checkCollision(Daggers::getDaggers()->at(j), enemiesObject[i]);

		for (int j = 0; j < HolyWater::getHolyWaters()->Count; j++)
			COLLISION->checkCollision(HolyWater::getHolyWaters()->at(j), enemiesObject[i]);

		for (int j = 0; j < ThrowingAxe::getThrowingAxes()->Count; j++)
			COLLISION->checkCollision(ThrowingAxe::getThrowingAxes()->at(j), enemiesObject[i]);
	}

	for (int i = 0; i < stairsObject.size(); i++)
		COLLISION->checkCollision(SIMON, stairsObject[i]);

	//BONETOWER_BULLET
	for (int i = 0; i < BONETOWER_BULLET->size(); i++)
	{
		COLLISION->checkCollision(WHIP, BONETOWER_BULLET->at(i));
		COLLISION->checkCollision(WHIPSITDOWN, BONETOWER_BULLET->at(i));
		COLLISION->checkCollision(SIMON, BONETOWER_BULLET->at(i));

		for (int j = 0; j < Boomerang::getBoomerangs()->Count; j++)
			COLLISION->checkCollision(Boomerang::getBoomerangs()->at(j), enemiesObject[i]);

		for (int j = 0; j < Daggers::getDaggers()->Count; j++)
			COLLISION->checkCollision(Daggers::getDaggers()->at(j), enemiesObject[i]);

		for (int j = 0; j < HolyWater::getHolyWaters()->Count; j++)
			COLLISION->checkCollision(HolyWater::getHolyWaters()->at(j), enemiesObject[i]);

		for (int j = 0; j < ThrowingAxe::getThrowingAxes()->Count; j++)
			COLLISION->checkCollision(ThrowingAxe::getThrowingAxes()->at(j), enemiesObject[i]);
	}

	//MEDUSA_SNAKE
	for (int i = 0; i < MEDUSA_SNAKE->size(); i++)
	{
		COLLISION->checkCollision(WHIP, MEDUSA_SNAKE->at(i));
		COLLISION->checkCollision(WHIPSITDOWN, MEDUSA_SNAKE->at(i));
		COLLISION->checkCollision(SIMON, MEDUSA_SNAKE->at(i));

		for (int j = 0; j < Boomerang::getBoomerangs()->Count; j++)
			COLLISION->checkCollision(Boomerang::getBoomerangs()->at(j), enemiesObject[i]);

		for (int j = 0; j < Daggers::getDaggers()->Count; j++)
			COLLISION->checkCollision(Daggers::getDaggers()->at(j), enemiesObject[i]);

		for (int j = 0; j < HolyWater::getHolyWaters()->Count; j++)
			COLLISION->checkCollision(HolyWater::getHolyWaters()->at(j), enemiesObject[i]);

		for (int j = 0; j < ThrowingAxe::getThrowingAxes()->Count; j++)
			COLLISION->checkCollision(ThrowingAxe::getThrowingAxes()->at(j), enemiesObject[i]);
	}

	//MUMMYMAN_BANDAGE
	for (int i = 0; i < MUMMYMAN_BANDAGE->size(); i++)
	{
		COLLISION->checkCollision(WHIP, MUMMYMAN_BANDAGE->at(i));
		COLLISION->checkCollision(WHIPSITDOWN, MUMMYMAN_BANDAGE->at(i));
		COLLISION->checkCollision(SIMON, MUMMYMAN_BANDAGE->at(i));

		for (int j = 0; j < Boomerang::getBoomerangs()->Count; j++)
			COLLISION->checkCollision(Boomerang::getBoomerangs()->at(j), enemiesObject[i]);

		for (int j = 0; j < Daggers::getDaggers()->Count; j++)
			COLLISION->checkCollision(Daggers::getDaggers()->at(j), enemiesObject[i]);

		for (int j = 0; j < HolyWater::getHolyWaters()->Count; j++)
			COLLISION->checkCollision(HolyWater::getHolyWaters()->at(j), enemiesObject[i]);

		for (int j = 0; j < ThrowingAxe::getThrowingAxes()->Count; j++)
			COLLISION->checkCollision(ThrowingAxe::getThrowingAxes()->at(j), enemiesObject[i]);
	}

	//SKELETON_BONE
	for (int i = 0; i < SKELETON_BONE->size(); i++)
	{
		COLLISION->checkCollision(WHIP, SKELETON_BONE->at(i));
		COLLISION->checkCollision(WHIPSITDOWN, SKELETON_BONE->at(i));
		COLLISION->checkCollision(SIMON, SKELETON_BONE->at(i));

		for (int j = 0; j < Boomerang::getBoomerangs()->Count; j++)
			COLLISION->checkCollision(Boomerang::getBoomerangs()->at(j), enemiesObject[i]);

		for (int j = 0; j < Daggers::getDaggers()->Count; j++)
			COLLISION->checkCollision(Daggers::getDaggers()->at(j), enemiesObject[i]);

		for (int j = 0; j < HolyWater::getHolyWaters()->Count; j++)
			COLLISION->checkCollision(HolyWater::getHolyWaters()->at(j), enemiesObject[i]);

		for (int j = 0; j < ThrowingAxe::getThrowingAxes()->Count; j++)
			COLLISION->checkCollision(ThrowingAxe::getThrowingAxes()->at(j), enemiesObject[i]);
	}

	if (GameState::curState == RUN)
	{
		for (int i = 0; i < enemiesObject.size(); i++)
			enemiesObject[i]->updateLocation();

		//MEDUSAHEADS
		for (int i = 0; i < MEDUSAHEADS->size(); i++)
		{
			MEDUSAHEADS->at(i)->updateLocation();
			if (MEDUSAHEADS->at(i)->allowDelete || (!CollisionManager::getInstance()->AABBCheck(*MEDUSAHEADS->at(i), *CAMERA)))
			{
				MedusaHead_List* medusahead_list = MEDUSAHEADS->at(i);
				MEDUSAHEADS->_Remove(medusahead_list);
				delete medusahead_list;
			}
		}

		//BONETOWER_BULLET
		for (int i = 0; i < BONETOWER_BULLET->size(); i++) 
		{
			BONETOWER_BULLET->at(i)->updateLocation();
			if (BONETOWER_BULLET->at(i)->allowDelete || (!CollisionManager::getInstance()->AABBCheck(*BONETOWER_BULLET->at(i), *CAMERA)))
			{
				BoneTower_Bullet* bonetower_bullet = BONETOWER_BULLET->at(i);
				BONETOWER_BULLET->_Remove(bonetower_bullet);
				delete bonetower_bullet;
			}
		}

		//MEDUSA_SNAKE
		for (int i = 0; i < MEDUSA_SNAKE->size(); i++) 
		{
			MEDUSA_SNAKE->at(i)->updateLocation();
			if (MEDUSA_SNAKE->at(i)->allowDelete || (!CollisionManager::getInstance()->AABBCheck(*MEDUSA_SNAKE->at(i), *CAMERA)))
			{
				Medusa_Snake* medusa_snake = MEDUSA_SNAKE->at(i);
				MEDUSA_SNAKE->_Remove(medusa_snake);
				delete medusa_snake;
			}
		}

		//MUMMYMAN_BANDAGE
		for (int i = 0; i < MUMMYMAN_BANDAGE->size(); i++)
		{
			MUMMYMAN_BANDAGE->at(i)->updateLocation();
			if (MUMMYMAN_BANDAGE->at(i)->allowDelete || (!CollisionManager::getInstance()->AABBCheck(*MUMMYMAN_BANDAGE->at(i), *CAMERA)))
			{
				MummyMan_Bandage* mummyman_bandage = MUMMYMAN_BANDAGE->at(i);
				MUMMYMAN_BANDAGE->_Remove(mummyman_bandage);
				delete mummyman_bandage;
			}
		}

		//SKELETON_BONE
		for (int i = 0; i < SKELETON_BONE->size(); i++)
		{
			SKELETON_BONE->at(i)->updateLocation();
			if (SKELETON_BONE->at(i)->allowDelete || (!CollisionManager::getInstance()->AABBCheck(*SKELETON_BONE->at(i), *CAMERA)))
			{
				Skeleton_Bone* skeleton_bone = SKELETON_BONE->at(i);
				SKELETON_BONE->_Remove(skeleton_bone);
				delete skeleton_bone;
			}
		}
	}

	SIMON->updateLocation();
	CAMERA->updateLocation();
	updateLocation();
}

void Map::draw()
{
	TileMap::render();

	List<Enemy*> enemiesObject = CAMERA->objectsInCamera.enemies;
	List<BaseObject*> itemsObject = CAMERA->objectsInCamera.items;
	List<BaseObject*> bridgesObject = CAMERA->objectsInCamera.bridges;
	List<BaseObject*> bricksObject = CAMERA->objectsInCamera.bricks;

	for (int i = 0; i < itemsObject.size(); i++)
		itemsObject[i]->draw();

	for (int i = 0; i < bridgesObject.size(); i++)
		bridgesObject[i]->draw();

	for (int i = 0; i < bricksObject.size(); i++)
		bricksObject[i]->draw();

	for (int i = 0; i < enemiesObject.size(); i++)
		enemiesObject[i]->draw();

	//MEDUSAHEADS
	for (int i = 0; i < MEDUSAHEADS->size(); i++)
		MEDUSAHEADS->at(i)->draw();

	//BONETOWER_BULLET
	for (int i = 0; i < BONETOWER_BULLET->size(); i++)
		BONETOWER_BULLET->at(i)->draw();

	//MEDUSA_SNAKE
	for (int i = 0; i < MEDUSA_SNAKE->size(); i++)
		MEDUSA_SNAKE->at(i)->draw();

	//MUMMYMAN_BANDAGE
	for (int i = 0; i < MUMMYMAN_BANDAGE->size(); i++)
		MUMMYMAN_BANDAGE->at(i)->draw();

	//SKELETON_BONE
	for (int i = 0; i < SKELETON_BONE->size(); i++)
		SKELETON_BONE->at(i)->draw();

	drawWeapon();
}

void Map::updateWeapon()
{
	for (int i = 0; i < Boomerang::getBoomerangs()->size(); i++)
	{
		Boomerang::getBoomerangs()->at(i)->update();
		COLLISION->checkCollision(Boomerang::getBoomerangs()->at(i), SIMON);
		Boomerang::getBoomerangs()->at(i)->updateLocation();

		if (Boomerang::getBoomerangs()->at(i)->allowDelete || (!CollisionManager::getInstance()->AABBCheck(*Boomerang::getBoomerangs()->at(i), *CAMERA)))
		{
			Boomerang* boomerang = Boomerang::getBoomerangs()->at(i);
			Boomerang::getBoomerangs()->_Remove(boomerang);
			delete boomerang;
			i--;
			SIMON->numberWeaponAppear++;
		}
	}

	for (int i = 0; i < Daggers::getDaggers()->size(); i++)
	{
		Daggers::getDaggers()->at(i)->update();
		Daggers::getDaggers()->at(i)->updateLocation();

		if (Daggers::getDaggers()->at(i)->allowDelete || (!CollisionManager::getInstance()->AABBCheck(*Daggers::getDaggers()->at(i), *CAMERA)))
		{
			Daggers* dagger = Daggers::getDaggers()->at(i);
			Daggers::getDaggers()->_Remove(dagger);
			delete dagger;
			i--;
			SIMON->numberWeaponAppear++;
		}
	}

	for (int i = 0; i < HolyWater::getHolyWaters()->size(); i++)
	{
		HolyWater::getHolyWaters()->at(i)->update();
		HolyWater::getHolyWaters()->at(i)->updateLocation();

		if (HolyWater::getHolyWaters()->at(i)->allowDelete || (!CollisionManager::getInstance()->AABBCheck(*HolyWater::getHolyWaters()->at(i), *CAMERA)))
		{
			HolyWater* holyWater = HolyWater::getHolyWaters()->at(i);
			HolyWater::getHolyWaters()->_Remove(holyWater);
			delete holyWater;
			i--;
			SIMON->numberWeaponAppear++;
		}
	}

	for (int i = 0; i < ThrowingAxe::getThrowingAxes()->size(); i++)
	{
		ThrowingAxe::getThrowingAxes()->at(i)->update();
		ThrowingAxe::getThrowingAxes()->at(i)->updateLocation();

		if (ThrowingAxe::getThrowingAxes()->at(i)->allowDelete || (!CollisionManager::getInstance()->AABBCheck(*ThrowingAxe::getThrowingAxes()->at(i), *CAMERA)))
		{
			ThrowingAxe* throwingAxe = ThrowingAxe::getThrowingAxes()->at(i);
			ThrowingAxe::getThrowingAxes()->_Remove(throwingAxe);
			delete throwingAxe;
			i--;
			SIMON->numberWeaponAppear++;
		}
	}
}

void Map::drawWeapon()
{
	for (int i = 0; i < Boomerang::getBoomerangs()->size(); i++)
		Boomerang::getBoomerangs()->at(i)->draw();

	for (int i = 0; i < Daggers::getDaggers()->size(); i++)
		Daggers::getDaggers()->at(i)->draw();

	for (int i = 0; i < HolyWater::getHolyWaters()->size(); i++)
		HolyWater::getHolyWaters()->at(i)->draw();

	for (int i = 0; i < ThrowingAxe::getThrowingAxes()->size(); i++)
		ThrowingAxe::getThrowingAxes()->at(i)->draw();
}

void Map::updateLocation()
{
	xMap -= CAMERA->dx;
	yMap -= CAMERA->dy;
}

Map::Map(void)
{
	xMap = X_MAP;
	yMap = Y_MAP;
	viewportWidth = VIEWPORT_WIDTH;
	viewportHeight = VIEWPORT_HEIGHT;
	CAMERA->x = -xMap;
	CAMERA->y = -yMap;
	CAMERA->width = viewportWidth;
	CAMERA->height = viewportHeight;
}

Map::~Map(void)
{
}
