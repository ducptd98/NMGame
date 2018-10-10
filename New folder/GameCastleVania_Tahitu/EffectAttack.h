#pragma once
#include "DrawableObject.h"

class EffectAttack : public DrawableObject
{
public:
	void draw(int xDraw, int yDraw);

	EffectAttack();
	~EffectAttack();
};

