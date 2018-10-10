#pragma once
#include "DrawableObject.h"

class Whip : public DrawableObject
{
	static Whip* instance;
public:
	static Whip* getInstance();

	static bool canAttack;
	int index;

	void update();
	void draw();

	Whip();
	~Whip();
};

