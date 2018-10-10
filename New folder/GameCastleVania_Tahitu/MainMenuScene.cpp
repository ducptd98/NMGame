#include "MainMenuScene.h"
#include "IntroScene.h"
#include "Graphics.h"
#include "CastleVaniaScene.h"

void MainMenuScene::init()
{
	img.Init("Data\\Background\\start_game.png", D3DCOLOR_XRGB(1, 1, 1));
	img1.Init("Data\\Background\\start.png", D3DCOLOR_XRGB(0, 0, 0));
}

void MainMenuScene::update()
{
	if (isStart)
	{
		if (timeDraw.canCreateFrame())
			isDraw = !isDraw;

		if (timeDraw.isTerminated())
		{
			Scene::changeScene(new CastleVaniaScene());
			Stage::curStage = Stage::curStages->at(0);
			Map::curMap->xMap = X_MAP;
			Map::curMap->yMap = Y_MAP;
			CAMERA->x = -Map::curMap->xMap;
			CAMERA->y = -Map::curMap->yMap;
			GAMESOUND->play(MUSIC_LEVEL2, true);
		}
	}

	if (KEY->keyChangeScenePress)
		isStart = true;
}

void MainMenuScene::draw()
{
	RECT r;
	SetRect(&r, 0, 0, 256, 224);
	img.RenderTexture(0, 0, &r);

	if (isDraw)
	{
		SetRect(&r, 0, 0, 100, 25);
		img1.RenderTexture(82, 130, &r);
	}
}

MainMenuScene::MainMenuScene()
{
	isDraw = true;
	isStart = false;
	timeDraw.init(0.3, 7);
	timeDraw.start();
}

MainMenuScene::~MainMenuScene()
{
}
