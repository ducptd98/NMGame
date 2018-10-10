#include "LifePlayer.h"
#include "Simon.h"

void LifePlayer::draw()
{
	for (int i = 0; i < LIFE; i++)
	{
		life[i].updateLocation();
		life[i].x += i * 8;
		life[i].draw();
	}
}

void LifePlayer::update()
{
	if (SIMON->life < 0)
	{
		for (int i = 0; i < LIFE; i++)
			life[i].curFrame = LT_EMPTY;

		return;
	}

	if (SIMON->life % 2 == 0)
	{
		for (int i = 0; i < SIMON->life / 2; i++)
			life[i].curFrame = LT_PLAYER;

		for (int i = SIMON->life / 2; i < LIFE; i++)
			life[i].curFrame = LT_EMPTY;
	}
	else
	{
		for (int i = 0; i < SIMON->life / 2; i++)
			life[i].curFrame = LT_PLAYER;

		life[SIMON->life / 2].curFrame = LT_HALF_PLAYER;

		for (int i = SIMON->life / 2 + 1; i < LIFE; i++)
			life[i].curFrame = LT_EMPTY;
	}
}

LifePlayer::LifePlayer()
{
	life = new Life[LIFE];
}

LifePlayer::~LifePlayer()
{
	delete[] life;
}
