#pragma once
#include "Scene.h"
#include "Scene.h"
#include "Sprite.h"
#include "Texture.h"
#include "DrawableObject.h"
#include "Graphics.h"
#include "Simon.h"
#include "SpearKnight.h"
#include "Map.h"
#include "Infomation.h"

class MapLevel3Scene : public Scene
{
public:
	Map map;
	Texture img;
	Infomation* info;
	static MapLevel3Scene* mapLevel3Scene;

	void init();
	void update();
	void draw();

	MapLevel3Scene();
	~MapLevel3Scene();
};

