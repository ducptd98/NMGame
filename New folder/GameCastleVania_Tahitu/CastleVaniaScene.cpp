#include "CastleVaniaScene.h"
#include "ChangeScene.h"
#include "MapLevel3Scene.h"
#include "GameOverScene.h"

CastleVaniaScene* CastleVaniaScene::castleVaniaScene;

void CastleVaniaScene::init()
{
	img.Init("Data\\Background\\top_background.png", D3DCOLOR_XRGB(1, 1, 1));
	map.init("Data\\Map\\level2\\level2.MatrixTile.txt", "Data\\Map\\level2\\level2.TileSheet.png", "Data\\Map\\level2\\level2.ObjectsMap.txt", "Data\\Map\\level2\\level2.QuadTree.txt");
	map.initStage("Data\\Map\\level2\\change_stage.txt");
}

void CastleVaniaScene::update()
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

	if (SIMON->level == 3)
	{
		GAMESOUND->play(MUSIC_LEVEL3, true);
		Scene::changeScene(new MapLevel3Scene());
		SIMON->x = 704;
		SIMON->y = 512;
		/*Map::curMap->xMap = -512;
		Map::curMap->yMap = -352;
		CAMERA->x = -Map::curMap->xMap;
		CAMERA->y = -Map::curMap->yMap;*/
		Stage::curStage = Stage::curStages->at(0);
		Stage::curStage->loadStageNext();
		return;
	}

	map.update();
	info->update();
}

void CastleVaniaScene::draw()
{
	map.draw();
	RECT r;
	SetRect(&r, 0, 0, 256, 48);
	img.RenderTexture(0, 0, &r);
	info->draw();
	SIMON->draw();
}

CastleVaniaScene::CastleVaniaScene(void)
{
	castleVaniaScene = this;
	info = new Infomation();
}

CastleVaniaScene::~CastleVaniaScene(void)
{
	delete info;
}
