#pragma once
#include "tilemap.h"
#include "Camera.h"
#include "QuadTree.h"
#include "Stage.h"

class Map : public TileMap
{
public:
	List<Stage*> stages;
	QuadTree quadtree;

	void init(const char* tileMatrixPath, const char* tileSheetPath, const char* objectsPath, const char* quadtreePath);
	void initStage(const char* stageInfoPath);

	void restoreAllObject();
	void update();
	void draw();
	void updateLocation();
	void updateWeapon();
	void drawWeapon();

	Map(void);
	~Map(void);
};

