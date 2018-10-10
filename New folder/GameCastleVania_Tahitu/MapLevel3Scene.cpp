#include "MapLevel3Scene.h"
#include "ChangeScene.h"
#include "WinGameScene.h"
#include "GameOverScene.h"

MapLevel3Scene* MapLevel3Scene::mapLevel3Scene;

void MapLevel3Scene::init()
{
	img.Init("Data\\Background\\top_background.png", D3DCOLOR_XRGB(1, 1, 1));
	map.init("Data\\Map\\level3\\level3.MatrixTile.txt", "Data\\Map\\level3\\level3.TileSheet.png", "Data\\Map\\level3\\level3.ObjectsMap.txt", "Data\\Map\\level3\\level3.QuadTree.txt");
	map.initStage("Data\\Map\\level3\\change_stage.txt");
}

void MapLevel3Scene::update()
{
	if (SIMON->numberOfAlive == 0)
	{
		Scene::changeScene(new GameOverScene());
		SIMON->numberOfAlive = 3;
		SIMON->level = 2;
		SIMON->x = 1824;
		SIMON->y = 706;
		WHIP->width = 23;
		WHIPSITDOWN->width = 23;
		return;
	}

	if (!SIMON->alive)
	{
		Scene::changeScene(new ChangeScene(), false);
		return;
	}

	if (SIMON->level == 4)
	{
		Scene::changeScene(new WinGameScene());
		SIMON->numberOfAlive = 3;
		SIMON->level = 2;
		SIMON->x = 1824;
		SIMON->y = 706;
		WHIP->width = 23;
		WHIPSITDOWN->width = 23;
		return;
	}

	map.update();
	info->update();
}

void MapLevel3Scene::draw()
{
	map.draw();
	RECT r;
	SetRect(&r, 0, 0, 256, 48);
	img.RenderTexture(0, 0, &r);
	info->draw();
	SIMON->draw();
}

MapLevel3Scene::MapLevel3Scene()
{
	mapLevel3Scene = this;
	info = new Infomation();
}


MapLevel3Scene::~MapLevel3Scene()
{
	delete info;
}
