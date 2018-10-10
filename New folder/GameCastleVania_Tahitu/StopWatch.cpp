#include "StopWatch.h"

StopWatch* StopWatch::instance = 0;
StopWatch* StopWatch::getInstance()
{
	if (instance == 0)
		instance = new StopWatch();

	return instance;
}

void StopWatch::update()
{
	if (onActive)
	{
		if (GameState::curState == RUN)
			SIMON->numberOfAttacks -= 5;

		GameState::curState = PAUSE_ENEMY;

		if (gameTimeLoop.canCreateFrame())
		{

		}

		if (gameTimeLoop.isTerminated())
		{
			onActive = false;
			gameTimeLoop.start();
			GameState::curState = RUN;
		}
	}
}

StopWatch::StopWatch()
{
	onActive = false;
	gameTimeLoop.init(1, 3);
	gameTimeLoop.start();
}

StopWatch::~StopWatch()
{
}
