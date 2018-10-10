#include "WindowGame.h"

WindowGame* WindowGame::instance = 0;
WindowGame* WindowGame::getInstance()
{
	if (instance == 0)
		instance = new WindowGame();
	return instance;
}

void WindowGame::initHandleWindows(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = CLASS_NAME;
	RegisterClassEx(&wcex);
	HWND hWnd = CreateWindow(CLASS_NAME, TITLE_STR, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	this->hWnd = hWnd;
}

HWND WindowGame::getHandleWindow()
{
	return hWnd;
}

LRESULT WindowGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

WindowGame::WindowGame(void)
{
}

WindowGame::~WindowGame(void)
{
}