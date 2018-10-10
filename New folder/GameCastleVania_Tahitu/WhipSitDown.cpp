#include "WhipSitDown.h"
#include "Simon.h"
#include "TileMap.h"
#include "WeaponLocations.h"

bool WhipSitDown::canAttack = false;

WhipSitDown* WhipSitDown::instance = 0;
WhipSitDown* WhipSitDown::getInstance()
{
	if (instance == 0)
		instance = new WhipSitDown();

	return instance;
}

void WhipSitDown::update()
{
	isCollisionCross = false;
	isCollision = false;

	if (index == 4)
		curAnimation = (curAnimation + 1) % 4;

	if (!pauseAnimation)
	{
		if (delayAnimation.canCreateFrame())
		{
			if (curFrame == sprite->animates[curAnimation].nFrame - 1)
			{
				curAnimation = nextAnimation;
				curFrame = sprite->animates[curAnimation].nFrame - 1;
			}

			sprite->animates[curAnimation].next(curFrame);
		}
	}
}

void WhipSitDown::draw()
{
	if (canAttack)
		canAttack = false;

	curFrame = SIMON->curFrame;
	int xInSimon = WEAPONLOCATION->ptsSitDown[curFrame].x;
	int yInSimon = WEAPONLOCATION->ptsSitDown[curFrame].y;

	if (curFrame != 2)
	{
		x = xInSimon + SIMON->x;
		y = yInSimon + SIMON->y;
	}
	else
	{
		x = SIMON->x + xInSimon - sprite->animates[0].frames[2].width;
		y = SIMON->y + yInSimon - sprite->animates[0].frames[2].height;
		x -= SIMON->updateX;
		canAttack = true;
		GAMESOUND->play(WHIP_SOUND, false);
	}

	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
	int trucQuay = xInViewport + SIMON->width / 2;

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}

	sprite->draw(xInViewport, yInViewport, 0, curFrame);

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}

	if (SIMON->direction == Right)
	{
		x = SIMON->x + SIMON->width;
		y = SIMON->y + yInSimon;
	}
}

WhipSitDown::WhipSitDown()
{
	index = 2;
	sprite = SPRITEMANAGER->sprites[index];
	direction = Left;
	width = sprite->animates[0].frames[2].width;
	height = sprite->animates[0].frames[2].height;
}

WhipSitDown::~WhipSitDown()
{
}
