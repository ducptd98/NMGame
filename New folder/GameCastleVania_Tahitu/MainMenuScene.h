#pragma once
#include "Scene.h"
#include "KeyGame.h"
#include "Texture.h"
#include "GameTimeLoop.h"

class MainMenuScene : public Scene
{
public:
	Texture img;
	Texture img1;
	bool isDraw;
	GameTimeLoop timeDraw;
	bool isStart;

	void init();
	void update();
	void draw();

	MainMenuScene();
	~MainMenuScene();
};

