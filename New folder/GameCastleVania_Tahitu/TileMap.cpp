#include "TileMap.h"
#include "SpriteManager.h"
#include "SpearKnight.h"
#include "Stairs.h"
#include "Simon.h"
#include "MedusaHead.h"
#include "DoorChangeStage.h"
#include "Item.h"
#include "WhipUpgrade.h"
#include "BoomerangItem.h"
#include "DaggerItem.h"
#include "HolyWaterItem.h"
#include "SmallHeart.h"
#include "LargeHeart.h"
#include "RedMoneyBag.h"
#include "PurpleMoneyBag.h"
#include "WhiteMoneyBag.h"
#include "Fleamen.h"
#include "Bridge.h"
#include "StopWatchItem.h"
#include "CrossItem.h"
#include "InvisibilityPotionItem.h"
#include "PorkChop.h"
#include "DoubleShotItem.h"
#include "TripleShotItem.h"
#include "BonusesItem.h"
#include "CrystalBallItem.h"
#include "CrownsItem.h"
#include "ChestsItem.h"
#include "Raven.h"
#include "Skeleton.h"
#include "Ghost.h"
#include "Bat.h"
#include "BoneTower.h"
#include "Brick.h"
#include "BlackItem.h"
#include "Medusa.h"
#include "MummyMan.h"
#include "ThrowingAxeItem.h"
#include "LongTrapLeft.h"
#include "ShortTrap.h"
#include "LongTrapRight.h"

TileMap* TileMap::curMap = 0;

void TileMap::convertToViewportPos(int xInMap, int yInMap, int & xViewport, int & yViewport)
{
	D3DXVECTOR3 posInMap;
	D3DXVECTOR4 posViewport;
	D3DXMATRIX mt;

	D3DXMatrixIdentity(&mt);
	mt._41 = (int)xMap;
	mt._42 = (int)yMap;

	posInMap.x = xInMap;
	posInMap.y = yInMap;
	posInMap.z = 0;

	D3DXVec3Transform(&posViewport, &posInMap, &mt);
	xViewport = posViewport.x;
	yViewport = posViewport.y;
}

void TileMap::renderTile(int rowIndex, int columnIndex)
{
	int xTileInViewport, yTileInViewport;
	int xTileInMap = columnIndex * 16;
	int yTileInMap = rowIndex * 16;
	int id = matrixTile[rowIndex][columnIndex];

	convertToViewportPos(xTileInMap, yTileInMap, xTileInViewport, yTileInViewport);

	RECT r;
	SetRect(&r, id * 16, 0, id * 16 + 16, 16);
	tileSheetImg.RenderTexture(xTileInViewport, yTileInViewport, &r);
}

void TileMap::renderTiles(int rowBegin, int rowEnd, int columnBegin, int columnEnd)
{
	if (rowBegin < 0 || columnBegin < 0 || rowEnd >= rowCount || columnEnd >= columnCount || rowBegin>rowEnd || columnBegin>columnEnd)
		return;

	for (int rowIndex = rowBegin; rowIndex <= rowEnd; rowIndex++)
		for (int columnIndex = columnBegin; columnIndex <= columnEnd; columnIndex++)
			renderTile(rowIndex, columnIndex);
}

void TileMap::render()
{
	int rowBegin, rowEnd, columnBegin, columnEnd;
	columnBegin = (-xMap) / 16;
	columnEnd = ((-xMap) + viewportWidth) / 16;
	rowBegin = (-yMap) / 16;
	rowEnd = ((-yMap) + viewportHeight) / 16;
	renderTiles(rowBegin, rowEnd, columnBegin, columnEnd);
}

TileMap::TileMap()
{
	curMap = this;
}
//add
void TileMap::initObjects(const char* objectsPath)
{
	fstream fs(objectsPath);
	fs >> nObjects;
	int id;
	float x, y, width, height;

	objects = new BaseObject*[nObjects];

	for (int i = 0; i < nObjects; i++)
	{
		fs >> id >> x >> y >> width >> height;

		switch (id % 100)
		{
		case SPR_SPEARKNIGHT:
			objects[i] = new SpearKnight();
			break;
		case SPR_MEDUSAHEAD:
			objects[i] = new MedusaHead();
			break;
		case SPR_GHOST:
			objects[i] = new Ghost();
			break;
		case SPR_BAT:
			objects[i] = new Bat();
			break;
		case SPR_BONETOWER:
			objects[i] = new BoneTower();
			break;
		case SPR_MEDUSA:
			objects[i] = new Medusa();
			break;
		case SPR_FLEAMEN:
			objects[i] = new Fleamen();
			break;
		case SPR_RAVEN:
			objects[i] = new Raven();
			break;
		case SPR_SKELETON:
			objects[i] = new Skeleton();
			break;
		case SPR_MUMMYMAN:
			objects[i] = new MummyMan();
			break;
		case SPR_STAIRS:
			objects[i] = new Stairs();
			break;
		case SPR_DOORCHANGESTAGE:
			objects[i] = new DoorChangeStage();
			break;
		case SPR_BRIDGE:
			objects[i] = new Bridge();
			break;
		case SPR_LONG_TRAP_LEFT:
			objects[i] = new LongTrapLeft();
			break;
		case SPR_SHORT_TRAP:
			objects[i] = new ShortTrap();
			break;
		case SPR_LONG_TRAP_RIGHT:
			objects[i] = new LongTrapRight();
			break;
		case SPR_BRICK:
			switch (id)
			{
			case BT_PORK_CHOP:
				objects[i] = new PorkChop();
				break;
			case BT_DOUBLE_SHOT:
				objects[i] = new DoubleShotItem();
				break;
			case BT_TRIPLE_SHOT:
				objects[i] = new TripleShotItem();
				break;
			case BT_BLACK:
				objects[i] = new BlackItem();
				break;
			default:
				break;
			}
			break;
		case SPR_BRICK_LEVEL3:
			switch (id)
			{
			case BT3_PORK_CHOP:
				objects[i] = new PorkChop();
				break;
			case BT3_DOUBLE_SHOT:
				objects[i] = new DoubleShotItem();
				break;
			case BT3_TRIPLE_SHOT:
				objects[i] = new TripleShotItem();
				break;
			case BT3_BLACK:
				objects[i] = new BlackItem();
				break;
			default:
				break;
			}
			break;
		case SPR_ITEM:
			switch (id)
			{
			case IT_WHIP_UPGRADE:
				objects[i] = new WhipUpgrade();
				break;
			case IT_BOOMERANG:
				objects[i] = new BoomerangItem();
				break;
			case IT_DAGGER:
				objects[i] = new DaggerItem();
				break;
			case IT_THROWING_AXE:
				objects[i] = new ThrowingAxeItem();
				break;
			case IT_HOLY_WATER:
				objects[i] = new HolyWaterItem();
				break;
			case IT_STOP_WATCH:
				objects[i] = new StopWatchItem();
				break;
			case IT_SMALL_HEART:
				objects[i] = new SmallHeart();
				break;
			case IT_LARGE_HEART:
				objects[i] = new LargeHeart();
				break;
			case IT_RED_MONEY_BAG:
				objects[i] = new RedMoneyBag();
				break;
			case IT_PURPLE_MONEY_BAG:
				objects[i] = new PurpleMoneyBag();
				break;
			case IT_WHITE_MONEY_BAG:
				objects[i] = new WhiteMoneyBag();
				break;
			case IT_CROSS:
				objects[i] = new CrossItem();
				break;
			case IT_INVISIBILITY_POTION:
				objects[i] = new InvisibilityPotionItem();
				break;
			case IT_BONUSES:
				objects[i] = new BonusesItem();
				break;
			case IT_CRYSTAL_BALL:
				objects[i] = new CrystalBallItem();
				break;
			case IT_CROWNS:
				objects[i] = new CrownsItem();
				break;
			case IT_CHESTS:
				objects[i] = new ChestsItem();
				break;
			default:
				break;
			}
			break;
		default:
			objects[i] = new BaseObject();
			break;
		}

		objects[i]->id = id;
		objects[i]->x = x;
		objects[i]->y = y;
		objects[i]->width = width;
		objects[i]->height = height;

		if (id >= 0)
		{
			DrawableObject* drawableObject = (DrawableObject*)objects[i];
			drawableObject->setSprite();
		}

		objects[i]->getFromObject(objects[i]);
	}

	fs.close();
}

void TileMap::init(const char * tileMatrixPath, const char * tileSheetPath, const char* objectsPath)
{
	fstream fs(tileMatrixPath);

	fs >> rowCount >> columnCount;

	matrixTile = new int*[rowCount];

	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
	{
		matrixTile[rowIndex] = new int[columnCount];

		for (int columnIndex = 0; columnIndex < columnCount; columnIndex++)
			fs >> matrixTile[rowIndex][columnIndex];
	}

	fs.close();

	tileSheetImg.Init(tileSheetPath, D3DCOLOR_XRGB(1, 1, 1));
	initObjects(objectsPath);
}

TileMap::~TileMap()
{
	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
		delete[] matrixTile[rowIndex];

	delete[] matrixTile;
}
