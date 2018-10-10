#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Texture.h"
#include "DrawableObject.h"
#include "Graphics.h"
#include "Simon.h"
#include "SpearKnight.h"
#include "Map.h"
#include "Infomation.h"

class CastleVaniaScene : public Scene
{
public:
	Map map;
	Texture img;
	Infomation* info;
	static CastleVaniaScene* castleVaniaScene;

	void init();
	void update();
	void draw();

	CastleVaniaScene(void);
	~CastleVaniaScene(void);
};


