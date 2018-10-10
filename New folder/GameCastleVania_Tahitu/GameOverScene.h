#pragma once
#include "Scene.h"
#include "KeyGame.h"
#include "Texture.h"
#include "GameTimeLoop.h"
#include "Number.h"

class GameOverScene : public Scene
{
public:
	Texture img;
	GameTimeLoop gameTimeLoop;
	Number* number;

	void init();
	void update();
	void draw();

	GameOverScene();
	~GameOverScene();
};

