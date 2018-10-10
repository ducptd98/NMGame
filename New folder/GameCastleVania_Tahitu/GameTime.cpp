#include "GameTime.h"

GameTime* GameTime::instance = 0;
GameTime* GameTime::getInstance()
{
	if (instance == 0)
		instance = new GameTime();
	return instance;
}

GameTime::GameTime(void)
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeStart);
}

bool GameTime::canCreateFrame()
{
	QueryPerformanceCounter(&timeEnd);
	frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)(timerFreq.QuadPart);

	if (frameTime < minFrameTime)
		return false;

	if (frameTime > maxFrameTime)
		frameTime = maxFrameTime;

	timeStart = timeEnd;

	return true;
}

GameTime::~GameTime(void)
{
}
