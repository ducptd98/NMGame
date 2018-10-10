#pragma once
#include "Scene.h"
#include "KeyGame.h"
#include "Texture.h"
#include "GameTimeLoop.h"

class WinGameScene : public Scene
{
public:
	Texture img;
	GameTimeLoop gameTimeLoop;

	void init();
	void update();
	void draw();

	WinGameScene();
	~WinGameScene();
};

