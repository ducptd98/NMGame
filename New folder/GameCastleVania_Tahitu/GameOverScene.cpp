#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "Map.h"
#include "Stage.h"
#include "Number.h"

void GameOverScene::init()
{
	img.Init("Data\\Background\\game_over.png", D3DCOLOR_XRGB(1, 1, 1));
}

void GameOverScene::update()
{
	gameTimeLoop.canCreateFrame();

	if (gameTimeLoop.isTerminated())
		if (KEY->keyChangeScenePress)
			Scene::changeScene(new MainMenuScene());
}

void GameOverScene::draw()
{
	RECT r;
	SetRect(&r, 0, 0, 256, 224);
	img.RenderTexture(0, 0, &r);

	for (int i = 0; i < 6; i++)
	{
		int x = 102 + i * 8;
		int y = 140;
		number[i].sprite->draw(x, y, 0, number[i].curFrame);
	}
}

GameOverScene::GameOverScene()
{
	gameTimeLoop.init(1.5, 1);
	gameTimeLoop.start();
	number = new Number[6];
	number[3].curFrame = (SIMON->score / 100) % 10;
	number[2].curFrame = (SIMON->score / 1000) % 10;
	number[1].curFrame = (SIMON->score / 10000) % 10;
	number[0].curFrame = (SIMON->score / 100000) % 10;
}

GameOverScene::~GameOverScene()
{
	delete[] number;
}
