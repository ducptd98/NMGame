#pragma once
#include "Constant.h"
#include <windows.h>

class GameTime
{
public:
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timerFreq;
	float minFrameTime;
	float maxFrameTime;
	static GameTime* instance;
	static GameTime* getInstance();
	float frameTime;

	bool canCreateFrame();

	GameTime(void);
	~GameTime(void);
};

