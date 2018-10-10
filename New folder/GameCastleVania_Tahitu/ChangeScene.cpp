#include "ChangeScene.h"
#include "CastleVaniaScene.h"
#include "MapLevel3Scene.h"
#include "Stage.h"
#include "Medusa.h"

void ChangeScene::init()
{
	img.Init("Data\\Background\\change_scene.png", D3DCOLOR_XRGB(1, 1, 1));
}

void ChangeScene::update()
{
	if (gameTimeLoop.canCreateFrame())
	{
		SIMON->numberOfAlive--;
		SIMON->life = 16;
		SIMON->onAreaBoss = false;
		SIMON->numberOfAttacks = 5;
		SIMON->numberWeaponAppear = 1;
		SIMON->numberAppear = 1;
		SIMON->weaponType = WT_DEFAULT;
		SIMON->timeDeath.start();
		SIMON->alive = true;
		SIMON->onStair = false;
		SIMON->onGoTo = false;
		WHIP->index = 2;
		WHIPSITDOWN->index = 2;
		WHIP->width = 23;
		WHIPSITDOWN->width = 23;
		WHIP->sprite = SPRITEMANAGER->sprites[WHIP->index];
		WHIPSITDOWN->sprite = SPRITEMANAGER->sprites[WHIPSITDOWN->index];

		if (SIMON->level == 2)
		{
			if (SIMON->numberOfAlive > 0)
				GAMESOUND->play(MUSIC_LEVEL2, true);
			Scene::curScene = CastleVaniaScene::castleVaniaScene;
		}

		if (SIMON->level == 3)
		{
			if (SIMON->numberOfAlive > 0)
				GAMESOUND->play(MUSIC_LEVEL3, true);
			Scene::curScene = MapLevel3Scene::mapLevel3Scene;
		}

		((Map*)Map::curMap)->restoreAllObject();

		if (SIMON->level == 2)
		{
			if (Stage::curStage->index == 0 || Stage::curStage->index == 1)
			{
				SIMON->x = 1824;
				SIMON->y = 706;
				Stage::curStage = Stage::curStages->at(0);
				Stage::curStage->loadStagePrev();
			}
			else if (Stage::curStage->index == 2 || Stage::curStage->index == 3)
			{
				SIMON->x = 1504;
				SIMON->y = 434;
				Stage::curStage = Stage::curStages->at(2);
				Stage::curStage->loadStageNext();
			}
			else if (Stage::curStage->index == 4 || Stage::curStage->index == 5 || Stage::curStage->index == 6)
			{
				SIMON->x = 736;
				SIMON->y = 290;
				Stage::curStage = Stage::curStages->at(4);
				Stage::curStage->loadStageNext();
			}
		}

		if (SIMON->level == 3)
		{
			if (Stage::curStage->index == 0 || Stage::curStage->index == 1)
			{
				SIMON->x = 704;
				SIMON->y = 512;
				Stage::curStage = Stage::curStages->at(0);
				Stage::curStage->loadStageNext();
			}
			else if (Stage::curStage->index == 2 || Stage::curStage->index == 3)
			{
				SIMON->x = 786;
				SIMON->y = 306;
				Stage::curStage = Stage::curStages->at(2);
				Stage::curStage->loadStageNext();
			}
			else if (Stage::curStage->index == 4 || Stage::curStage->index == 5)
			{
				SIMON->x = 2080;
				SIMON->y = 96;
				Stage::curStage = Stage::curStages->at(4);
				Stage::curStage->loadStageNext();
			}
		}
	}
}

void ChangeScene::draw()
{
	RECT r;
	SetRect(&r, 0, 0, 256, 224);
	img.RenderTexture(0, 0, &r);
}

ChangeScene::ChangeScene()
{
	gameTimeLoop.init(1, 1);
	gameTimeLoop.start();
}

ChangeScene::~ChangeScene()
{
}
