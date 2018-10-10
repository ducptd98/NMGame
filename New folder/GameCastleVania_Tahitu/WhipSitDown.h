#pragma once
#include "DrawableObject.h"

class WhipSitDown : public DrawableObject
{
	static WhipSitDown* instance;
public:
	static WhipSitDown* getInstance();

	static bool canAttack;
	int index;

	void update();
	void draw();

	WhipSitDown();
	~WhipSitDown();
};

