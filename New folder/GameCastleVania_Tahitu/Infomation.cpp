#include "Infomation.h"

void Infomation::draw()
{
	time->draw();
	stageNumber->draw();
	numberOfAttack->draw();
	lifePlayer->draw();
	lifeEnemy->draw();
	score->draw();
	weaponType->draw();
	numberOfAlive->draw();
	numberWeaponAppear->draw();
}

void Infomation::update()
{
	time->update();
	score->update();
	numberOfAttack->update();
	lifePlayer->update();
	lifeEnemy->update();
	stageNumber->update();
	weaponType->update();
	numberOfAlive->update();
	numberWeaponAppear->update();
}

Infomation::Infomation()
{
	time = new Time();
	stageNumber = new StageNumber();
	numberOfAttack = new NumberOfAttack();
	lifePlayer = new LifePlayer();
	lifeEnemy = new LifeEnemy();
	score = new Score();
	weaponType = new WeaponType();
	numberOfAlive = new NumberOfAlive();
	numberWeaponAppear = new NumberWeaponAppear();
}

Infomation::~Infomation()
{
	delete time;
	delete stageNumber;
	delete numberOfAttack;
	delete lifePlayer;
	delete lifeEnemy;
	delete score;
	delete weaponType;
	delete numberOfAlive;
	delete numberWeaponAppear;
}
