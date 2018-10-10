#pragma once
#include "Time.h"
#include "StageNumber.h"
#include "NumberOfAttack.h"
#include "LifePlayer.h"
#include "LifeEnemy.h"
#include "Score.h"
#include "WeaponType.h"
#include "NumberOfAlive.h"
#include "NumberWeaponAppear.h"

class Infomation
{
public:
	Time* time;
	StageNumber* stageNumber;
	NumberOfAttack* numberOfAttack;
	LifePlayer* lifePlayer;
	LifeEnemy* lifeEnemy;
	Score* score;
	WeaponType* weaponType;
	NumberOfAlive* numberOfAlive;
	NumberWeaponAppear* numberWeaponAppear;

	void draw();
	void update();

	Infomation();
	~Infomation();
};

