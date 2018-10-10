#pragma once
#include "Scene.h"
#include "Texture.h"
#include "GameTimeLoop.h"

class ChangeScene : public Scene
{
public:
	Texture img;
	GameTimeLoop gameTimeLoop;

	void init();
	void update();
	void draw();

	ChangeScene();
	~ChangeScene();
};

