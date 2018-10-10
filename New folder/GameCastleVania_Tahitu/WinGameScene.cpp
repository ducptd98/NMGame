#include "WinGameScene.h"
#include "MainMenuScene.h"
#include "Map.h"
#include "Stage.h"

void WinGameScene::init()
{
	img.Init("Data\\Background\\win_game.png", D3DCOLOR_XRGB(1, 1, 1));
}

void WinGameScene::update()
{
	gameTimeLoop.canCreateFrame();

	if (gameTimeLoop.isTerminated())
		if (KEY->keyChangeScenePress)
			Scene::changeScene(new MainMenuScene());
}

void WinGameScene::draw()
{
	RECT r;
	SetRect(&r, 0, 0, 256, 224);
	img.RenderTexture(0, 0, &r);
}

WinGameScene::WinGameScene()
{
	gameTimeLoop.init(3, 1);
	gameTimeLoop.start();
}

WinGameScene::~WinGameScene()
{
}
