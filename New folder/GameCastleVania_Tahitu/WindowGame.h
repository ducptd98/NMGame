#pragma once
#include "Constant.h"
#include <Windows.h>

class WindowGame
{
private:
	HWND hWnd;

	static WindowGame* instance;
public:
	static WindowGame* getInstance();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void initHandleWindows(HINSTANCE hInstance, int nCmdShow);
	HWND getHandleWindow();

	WindowGame(void);
	~WindowGame(void);
};

