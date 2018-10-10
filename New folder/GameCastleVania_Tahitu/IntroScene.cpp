#include "IntroScene.h"
#include "CastleVaniaScene.h"
#include "Graphics.h"

void IntroScene::init()
{
	img.Init("Data\\Background\\intro.png", D3DCOLOR_XRGB(1, 1, 1));
}

void IntroScene::update()
{
	
}

void IntroScene::draw()
{
	RECT r;
	SetRect(&r, 0, 0, 256, 224);
	img.RenderTexture(0, 0, &r);
}

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}
