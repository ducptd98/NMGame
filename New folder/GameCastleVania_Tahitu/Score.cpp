#include "Score.h"
#include "Simon.h"

void Score::draw()
{
	for (int i = 0; i < 6; i++)
	{
		number[i].updateLocation();
		number[i].x -= 96 - i * 8;
		number[i].draw();
	}
}

void Score::update()
{
	if (number[3].gameTimeLoop.canCreateFrame())
	{
		number[3].curFrame = (SIMON->score / 100) % 10;
		number[2].curFrame = (SIMON->score / 1000) % 10;
		number[1].curFrame = (SIMON->score / 10000) % 10;
		number[0].curFrame = (SIMON->score / 100000) % 10;
	}

	if (number[3].gameTimeLoop.isTerminated())
		number[3].gameTimeLoop.start();
}

Score::Score()
{
	number = new Number[6];

	for (int i = 0; i < 6; i++)
		number[i].gameTimeLoop.init(0.2, 400);
}

Score::~Score()
{
	delete[] number;
}
