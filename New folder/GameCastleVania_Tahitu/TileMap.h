#pragma once
#include "Texture.h"
#include "BaseObject.h"
#include <fstream>
using namespace std;

class TileMap
{
public:
	float viewportWidth, viewportHeight;
	float xMap, yMap;
	int nObjects;
	BaseObject** objects;
	static TileMap* curMap;
	int** matrixTile;
	Texture tileSheetImg;
	int rowCount, columnCount;

	void convertToViewportPos(int xInMap, int yInMap, int& xViewport, int& yViewport);
	void renderTile(int rowIndex, int columnIndex);
	void renderTiles(int rowBegin, int rowEnd, int columnBegin, int columnEnd);
	void render();
	void init(const char* tileMatrixPath, const char* tileSheetPath, const char* objectsPath);
	void initObjects(const char* objectsPath);

	TileMap();
	~TileMap();
};

