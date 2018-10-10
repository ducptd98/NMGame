#include "Time.h"
#include "Simon.h"

void Time::draw()
{			
	for (int i = 0; i < 4; i++)
	{
		number[i].updateLocation();
		number[i].x += i * 8;
		number[i].draw();
	}
}

void Time::update()
{
	if (!SIMON->alive)
	{
		number[1].curFrame = 4;
		number[2].curFrame = 0;
		number[3].curFrame = 1;
		down = true;
	}

	if (number[3].curFrame == 0 && number[2].curFrame == 0 && number[1].curFrame == 0)
	{
		SIMON->isDeath = true;
		SIMON->changeAction(SA_DEATH);
		SIMON->dx = 0;
		return;
	}

	if (number[3].gameTimeLoop.canCreateFrame())
	{
		number[3].next(number[3].curFrame);

		if (number[3].curFrame == 9)
			number[2].next(number[2].curFrame);

		if (number[2].curFrame == 8)
			down = true;

		if (number[2].curFrame == 9 && down)
		{
			number[1].next(number[1].curFrame);
			down = false;
		}
	}

	if (number[3].gameTimeLoop.isTerminated())
		number[3].gameTimeLoop.start();
}

Time::Time()
{
	number = new Number[4];
	number[1].curFrame = 4;
	down = true;
}

Time::~Time()
{
	delete[] number;
}
