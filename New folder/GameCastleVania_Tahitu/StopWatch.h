#pragma once
#include "GameTimeLoop.h"
#include "GameState.h"
#include "Simon.h"

class StopWatch
{
	static StopWatch* instance;
public:
	static StopWatch* getInstance();

	bool onActive;
	GameTimeLoop gameTimeLoop;

	void update();

	StopWatch();
	~StopWatch();
};

