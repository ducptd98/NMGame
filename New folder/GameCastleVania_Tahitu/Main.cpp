#include "WindowGame.h"
#include "Graphics.h"
#include "Texture.h"
#include "KeyGame.h"
#include "MainMenuScene.h"
#include "MapLevel3Scene.h"
#include "CastleVaniaScene.h"
#include "MapLevel3Scene.h"
#include "GameSound.h"
#include <Windows.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WINDOW->initHandleWindows(hInstance, nCmdShow);

	CastleVaniaScene::changeScene(new MainMenuScene());

	Keyboard::Create(hInstance, WINDOW->getHandleWindow());

	GAME_TIME->minFrameTime = MIN_FRAME_TIME;
	GAME_TIME->maxFrameTime = MAX_FRAME_TIME;

	GameSound::initialize(WINDOW->getHandleWindow());

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//GAMESOUND->play(MUSIC_LEVEL3, true);

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (GAME_TIME->canCreateFrame())
			{
				KEYBOARD->PollKeyboard();
				KEYBOARD->UpdateKeyboard();
				KEY->update();
				CURSCENE->update();
				GRAPHICS->BeginGraphics();
				//code ve len backbuffer
				CURSCENE->draw();
				GRAPHICS->EndGraphics();
				//ve backbuffer len framebuffer
				GRAPHICS->PresentBackBuffer();
			}
			else
			{
				timeBeginPeriod(1);
				Sleep((DWORD)(1000 * (GAME_TIME->minFrameTime)));
				timeEndPeriod(1);
			}
		}
	}

	delete WINDOW;
	delete GRAPHICS;

	if (CastleVaniaScene::curScene != 0)
		delete CastleVaniaScene::curScene;

	return nCmdShow;
}
