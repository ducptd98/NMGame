#include "Item.h"
#include "Simon.h"
#include "HolyWater.h"
#include "Boomerang.h"
#include "GameState.h"
#include "Enemy.h"
#include "List.h"
#include "Camera.h"
#include "Medusa.h"

void Item::onAABBCheck(BaseObject * other)
{
	if (((other == WHIP && WHIP->canAttack) || other->collisionType == CT_WEAPON) && curAnimation == IA_DEFAULT)
	{
		GameSound::getInstance()->play(ENEMY_HIT1, false);
		gameTimeLoop.start();

		if (SIMON->weaponType != WT_BOOMERANG)
			other->allowDelete = true;

		switch (itemType)
		{
		case IT_WHIP_UPGRADE:
			curAnimation = IA_WHIP_UPGRADE;
			nextAnimation = IA_WHIP_UPGRADE;
			dy = 1;
			break;
		case IT_BOOMERANG:
			curAnimation = IA_BOOMERANG;
			nextAnimation = IA_BOOMERANG;
			dy = 1;
			break;
		case IT_DAGGER:
			curAnimation = IA_DAGGER;
			nextAnimation = IA_DAGGER;
			dy = 1;
			break;
		case IT_THROWING_AXE:
			curAnimation = IA_THROWING_AXE;
			nextAnimation = IA_THROWING_AXE;
			dy = 1;
			break;
		case IT_HOLY_WATER:
			curAnimation = IA_HOLY_WATER;
			nextAnimation = IA_HOLY_WATER;
			dy = 1;
			break;
		case IT_STOP_WATCH:
			curAnimation = IA_STOP_WATCH;
			nextAnimation = IA_STOP_WATCH;
			dy = 1;
			break;
		case IT_SMALL_HEART:
			curAnimation = IA_SMALL_HEART;
			nextAnimation = IA_SMALL_HEART;
			dy = 1;
			break;
		case IT_LARGE_HEART:
			curAnimation = IA_LARGE_HEART;
			nextAnimation = IA_LARGE_HEART;
			dy = 1;
			break;
		case IT_RED_MONEY_BAG:
			curAnimation = IA_RED_MONEY_BAG;
			nextAnimation = IA_RED_MONEY_BAG;
			dy = 1;
			break;
		case IT_PURPLE_MONEY_BAG:
			curAnimation = IA_PURPLE_MONEY_BAG;
			nextAnimation = IA_PURPLE_MONEY_BAG;
			dy = 1;
			break;
		case IT_WHITE_MONEY_BAG:
			curAnimation = IA_WHITE_MONEY_BAG;
			nextAnimation = IA_WHITE_MONEY_BAG;
			dy = 1;
			break;
		case IT_CROSS:
			curAnimation = IA_CROSS;
			nextAnimation = IA_CROSS;
			dy = 1;
			break;
		case IT_INVISIBILITY_POTION:
			curAnimation = IA_INVISIBILITY_POTION;
			nextAnimation = IA_INVISIBILITY_POTION;
			dy = 1;
			break;
		default:
			break;
		}
	}

	List<Enemy*>* enemiesObject;

	if (other == SIMON && curAnimation != IA_DEFAULT)
	{
		switch (itemType)
		{
		case IT_WHIP_UPGRADE:
			if (WHIP->index < 4)
			{
				WHIP->index++;
				WHIPSITDOWN->index++;
				WHIP->sprite = SPRITEMANAGER->sprites[WHIP->index];
				WHIPSITDOWN->sprite = SPRITEMANAGER->sprites[WHIPSITDOWN->index];
				if (WHIP->index == 4)
				{
					WHIP->width = 42;
					WHIPSITDOWN->width = 42;
				}
				SIMON->onPickUpItem = true;
				SIMON->curAnimation = SA_PICKUP_ITEM;
				SIMON->curFrame = 0;
				SIMON->timePickUpItem.start();
				GAMESOUND->play(WHIP_POWERUP_AND_WEAPONGET, false);
				GameState::curState = PAUSE;
			}
			break;
		case IT_BOOMERANG:
			SIMON->weaponType = WT_BOOMERANG;
			SIMON->numberWeaponAppear = 1;
			SIMON->numberAppear = 1;
			break;
		case IT_DAGGER:
			SIMON->weaponType = WT_DAGGER;
			SIMON->numberWeaponAppear = 1;
			SIMON->numberAppear = 1;
			break;
		case IT_THROWING_AXE:
			SIMON->weaponType = WT_THROWING_AXE;
			SIMON->numberWeaponAppear = 1;
			SIMON->numberAppear = 1;
			break;
		case IT_HOLY_WATER:
			SIMON->weaponType = WT_HOLY_WATER;
			SIMON->numberWeaponAppear = 1;
			SIMON->numberAppear = 1;
			break;
		case IT_STOP_WATCH:
			SIMON->weaponType = WT_STOPWATCH;
			SIMON->numberWeaponAppear = 1;
			SIMON->numberAppear = 1;
			break;
		case IT_SMALL_HEART:
			SIMON->numberOfAttacks++;
			GAMESOUND->play(HEART, false);
			break;
		case IT_LARGE_HEART:
			SIMON->numberOfAttacks += 5;
			GAMESOUND->play(HEART, false);
			break;
		case IT_RED_MONEY_BAG:
			SIMON->score += 100;
			break;
		case IT_PURPLE_MONEY_BAG:
			SIMON->score += 400;
			break;
		case IT_WHITE_MONEY_BAG:
			SIMON->score += 700;
			break;
		case IT_CROSS:
			enemiesObject = &CAMERA->objectsInCamera.enemies;
			for (int i = 0; i < enemiesObject->size(); i++)
				enemiesObject->at(i)->alive = false;
			break;
		case IT_INVISIBILITY_POTION:
			SIMON->gameTimeLoop.start();
			SIMON->invisibilityPoint = true;
			break;
		case IT_BONUSES:
			SIMON->score += 1000;
			break;
		case IT_CRYSTAL_BALL:
			timeNextLevel.start();
			isNextLevel = true;
			SIMON->onAreaBoss = false;
			SIMON->stage++;
			SIMON->life = 16;
			Medusa::lifeBoss = 16;
			Medusa::isDeath = false;
			GAMESOUND->play(STAGE_CLEAR, false);
			break;
		case IT_CROWNS:
			SIMON->score += 2000;
			break;
		case IT_CHESTS:
			SIMON->score += 2000;
			break;
		default:
			break;
		}

		alive = false;
	}
}

void Item::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
}

void Item::restore(BaseObject * obj)
{
	dy = 0;
	vy = 0;
	DrawableObject::restore(obj);
}

void Item::update()
{
	if (curAnimation != IA_DEFAULT && gameTimeLoop.canCreateFrame())
		alive = false;

	if (curAnimation == IA_DEFAULT)
	{
		DrawableObject::update();
		return;
	}

	MovableObject::update();
}

Item::Item()
{
	collisionType = CT_ITEM;
	gameTimeLoop.init(3, 1);
	isNextLevel = false;
	timeNextLevel.init(3, 1);
}

Item::~Item()
{
}
