#include "EffectAttack.h"
#include "TileMap.h"

void EffectAttack::draw(int xDraw, int yDraw)
{
	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(xDraw, yDraw, xInViewport, yInViewport);
	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
}

EffectAttack::EffectAttack()
{
	sprite = SPRITEMANAGER->sprites[SPR_ATTACKENEMY];
}

EffectAttack::~EffectAttack()
{
}
