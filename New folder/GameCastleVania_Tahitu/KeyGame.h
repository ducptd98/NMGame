#pragma once
#include "Keyboard.h"
#include "Constant.h"

class KeyGame
{
private:
	Keyboard* key;

	static KeyGame* instance;
public:
	static KeyGame* getInstance();

	bool keyUp;
	bool keyDown;
	bool keyLeft;
	bool keyRight;
	bool keyMove;
	bool keyStair;
	bool keyBeginStair;
	bool keyRangeAttack;
	bool keySitDownAttack;

	bool keyChangeScene;
	bool keyChangeScenePress, isKeyChangeSceneDownPrevious;

	bool keyAttack;
	bool keyAttackPress, isKeyAttackDownPrevious;

	bool keyJump;
	bool keyJumpPress, isKeyJumpDownPrevious;

	void update();

	KeyGame();
	~KeyGame();
};

