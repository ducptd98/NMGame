#pragma once
#include "Scene.h"
#include "KeyGame.h"
#include "Texture.h"

class IntroScene : public Scene
{
public:
	Texture img;

	void init();
	void update();
	void draw();

	IntroScene();
	~IntroScene();
};

