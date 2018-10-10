#include "LifeEnemy.h"
#include "Medusa.h"
#include "Simon.h"

void LifeEnemy::draw()
{
	for (int i = 0; i < LIFE; i++)
	{
		life[i].updateLocation();
		life[i].x += i * 8;
		life[i].y += 12;
		life[i].draw();
	}
};

void LifeEnemy::update()
{
	if (SIMON->level == 2)
	{
		if (Medusa::lifeBoss < 0)
		{
			for (int i = 0; i < LIFE; i++)
				life[i].curFrame = LT_EMPTY;

			return;
		}

		if (Medusa::lifeBoss % 2 == 0)
		{
			for (int i = 0; i < Medusa::lifeBoss / 2; i++)
				life[i].curFrame = LT_ENEMY;

			for (int i = Medusa::lifeBoss / 2; i < LIFE; i++)
				life[i].curFrame = LT_EMPTY;
		}
		else
		{
			for (int i = 0; i < Medusa::lifeBoss / 2; i++)
				life[i].curFrame = LT_ENEMY;

			life[Medusa::lifeBoss / 2].curFrame = LT_HALF_ENEMY;

			for (int i = Medusa::lifeBoss / 2 + 1; i < LIFE; i++)
				life[i].curFrame = LT_EMPTY;
		}
	}

	if (SIMON->level == 3)
	{
		if (Medusa::lifeBoss < 0)
		{
			for (int i = 0; i < LIFE; i++)
				life[i].curFrame = LT_EMPTY;

			return;
		}

		if (Medusa::lifeBoss % 2 == 0)
		{
			for (int i = 0; i < Medusa::lifeBoss / 2; i++)
				life[i].curFrame = LT_ENEMY;

			for (int i = Medusa::lifeBoss / 2; i < LIFE; i++)
				life[i].curFrame = LT_EMPTY;
		}
		else
		{
			for (int i = 0; i < Medusa::lifeBoss / 2; i++)
				life[i].curFrame = LT_ENEMY;

			life[Medusa::lifeBoss / 2].curFrame = LT_HALF_ENEMY;

			for (int i = Medusa::lifeBoss / 2 + 1; i < LIFE; i++)
				life[i].curFrame = LT_EMPTY;
		}
	}
}

LifeEnemy::LifeEnemy()
{
	life = new Life[LIFE];
}

LifeEnemy::~LifeEnemy()
{
	delete[] life;
}
