#include "KeyGame.h"

KeyGame* KeyGame::instance = 0;
KeyGame*  KeyGame::getInstance()
{
	if (instance == 0)
		instance = new KeyGame();

	return instance;
}

void KeyGame::update()
{
	keyAttack = key->IsKeyDown(DIK_Z) || key->IsKeyDown(DIK_L);
	keyAttackPress = keyAttack && !isKeyAttackDownPrevious;
	isKeyAttackDownPrevious = keyAttack;

	keyJump = key->IsKeyDown(DIK_SPACE);
	keyJumpPress = keyJump && !isKeyJumpDownPrevious;
	isKeyJumpDownPrevious = keyJump;

	keyChangeScene = key->IsKeyDown(DIK_RETURN);
	keyChangeScenePress = keyChangeScene && !isKeyChangeSceneDownPrevious;
	isKeyChangeSceneDownPrevious = keyChangeScene;

	keyUp = key->IsKeyDown(DIK_UP) || key->IsKeyDown(DIK_W);
	keyDown = key->IsKeyDown(DIK_DOWN) || key->IsKeyDown(DIK_S);
	keyLeft = key->IsKeyDown(DIK_LEFT) || key->IsKeyDown(DIK_A);
	keyRight = key->IsKeyDown(DIK_RIGHT) || key->IsKeyDown(DIK_D);
	keyMove = keyLeft || keyRight;
	keyStair = keyUp || keyDown || keyLeft || keyRight;
	keyBeginStair = keyUp;
	keyRangeAttack = keyUp && keyAttackPress;
	keySitDownAttack = keyDown && keyAttackPress;
}

KeyGame::KeyGame()
{
	key = KEYBOARD;
	isKeyJumpDownPrevious = false;
	isKeyAttackDownPrevious = false;
	isKeyChangeSceneDownPrevious = false;
}

KeyGame::~KeyGame()
{
}
