#include "SpriteManager.h"

SpriteManager* SpriteManager::instance = 0;
SpriteManager* SpriteManager::getInstance()
{
	if (instance == 0)
		instance = new SpriteManager();
	return instance;
}

//add
SpriteManager::SpriteManager()
{
	sprites = new Sprite*[SPR_COUNT];
	sprites[SPR_SIMON] = new Sprite("Data\\Player\\simon.png", "Data\\Player\\simon.txt");
	sprites[SPR_DOORCHANGESTAGE] = new Sprite("Data\\Door\\door.png", "Data\\Door\\door.txt");
	sprites[SPR_ITEM] = new Sprite("Data\\Item\\item.png", "Data\\Item\\item.txt");
	sprites[SPR_BRICK] = new Sprite("Data\\Item\\item.png", "Data\\Item\\brick.txt");
	sprites[SPR_BRICK_LEVEL3] = new Sprite("Data\\Item\\item.png", "Data\\Item\\brick_level3.txt");
	sprites[SPR_LONG_TRAP_LEFT] = new Sprite("Data\\Trap\\trap.png", "Data\\Trap\\trap.txt");
	sprites[SPR_SHORT_TRAP] = new Sprite("Data\\Trap\\trap.png", "Data\\Trap\\trap.txt");
	sprites[SPR_LONG_TRAP_RIGHT] = new Sprite("Data\\Trap\\trap.png", "Data\\Trap\\trap.txt");
	sprites[SPR_INFOMATION] = new Sprite("Data\\Background\\infomation.png", "Data\\Background\\infomation.txt");
	sprites[SPR_SPEARKNIGHT] = new Sprite("Data\\Enemy\\enemies.png", "Data\\Enemy\\spearknights.txt");
	sprites[SPR_MEDUSA] = new Sprite("Data\\Boss\\boss.png", "Data\\Boss\\medusa.txt");

	//---------------------------------------------------------Enemies
	enemies = sprites[SPR_SPEARKNIGHT]->image;

	sprites[SPR_MEDUSAHEAD] = new Sprite();
	sprites[SPR_MEDUSAHEAD]->image = enemies;
	sprites[SPR_MEDUSAHEAD]->initAnimation("Data\\Enemy\\medusahead.txt");

	sprites[SPR_GHOST] = new Sprite();
	sprites[SPR_GHOST]->image = enemies;
	sprites[SPR_GHOST]->initAnimation("Data\\Enemy\\ghost.txt");

	sprites[SPR_BAT] = new Sprite();
	sprites[SPR_BAT]->image = enemies;
	sprites[SPR_BAT]->initAnimation("Data\\Enemy\\bat.txt");

	sprites[SPR_BONETOWER] = new Sprite();
	sprites[SPR_BONETOWER]->image = enemies;
	sprites[SPR_BONETOWER]->initAnimation("Data\\Enemy\\bonetower.txt");

	sprites[SPR_BONETOWER_BULLET] = new Sprite();
	sprites[SPR_BONETOWER_BULLET]->image = enemies;
	sprites[SPR_BONETOWER_BULLET]->initAnimation("Data\\Enemy\\bonetower_bullet.txt");

	sprites[SPR_FLEAMEN] = new Sprite();
	sprites[SPR_FLEAMEN]->image = enemies;
	sprites[SPR_FLEAMEN]->initAnimation("Data\\Enemy\\fleamen.txt");

	sprites[SPR_RAVEN] = new Sprite();
	sprites[SPR_RAVEN]->image = enemies;
	sprites[SPR_RAVEN]->initAnimation("Data\\Enemy\\raven.txt");

	sprites[SPR_SKELETON] = new Sprite();
	sprites[SPR_SKELETON]->image = enemies;
	sprites[SPR_SKELETON]->initAnimation("Data\\Enemy\\skeleton.txt");

	sprites[SPR_SKELETON_BONE] = new Sprite();
	sprites[SPR_SKELETON_BONE]->image = enemies;
	sprites[SPR_SKELETON_BONE]->initAnimation("Data\\Enemy\\skeleton_bone.txt");

	sprites[SPR_DELETEOBJECT] = new Sprite();
	sprites[SPR_DELETEOBJECT]->image = enemies;
	sprites[SPR_DELETEOBJECT]->initAnimation("Data\\Enemy\\deleteobject.txt");

	sprites[SPR_ATTACKENEMY] = new Sprite();
	sprites[SPR_ATTACKENEMY]->image = enemies;
	sprites[SPR_ATTACKENEMY]->initAnimation("Data\\Enemy\\attackenemy.txt");

	//---------------------------------------------------------Bosses
	bosses = sprites[SPR_MEDUSA]->image;

	sprites[SPR_MEDUSA_SNAKE] = new Sprite();
	sprites[SPR_MEDUSA_SNAKE]->image = bosses;
	sprites[SPR_MEDUSA_SNAKE]->initAnimation("Data\\Boss\\snake.txt");

	sprites[SPR_MUMMYMAN] = new Sprite();
	sprites[SPR_MUMMYMAN]->image = bosses;
	sprites[SPR_MUMMYMAN]->initAnimation("Data\\Boss\\mummy.txt");

	sprites[SPR_MUMMYMAN_BANDAGE] = new Sprite();
	sprites[SPR_MUMMYMAN_BANDAGE]->image = bosses;
	sprites[SPR_MUMMYMAN_BANDAGE]->initAnimation("Data\\Boss\\bandage.txt");

	sprites[SPR_KILL_BOSS] = new Sprite();
	sprites[SPR_KILL_BOSS]->image = bosses;
	sprites[SPR_KILL_BOSS]->initAnimation("Data\\Boss\\kill_boss.txt");

	//---------------------------------------------------------Weapon
	sprites[SPR_WHIP1] = new Sprite("Data\\Player\\Whip\\whip1.png", "Data\\Player\\Whip\\whip1.txt");
	sprites[SPR_WHIP2] = new Sprite("Data\\Player\\Whip\\whip2.png", "Data\\Player\\Whip\\whip2.txt");
	sprites[SPR_WHIP3] = new Sprite("Data\\Player\\Whip\\whip3.png", "Data\\Player\\Whip\\whip3.txt");

	sprites[SPR_DAGGER] = new Sprite("Data\\Player\\Weapon\\dagger.png", "Data\\Player\\Weapon\\dagger.txt");
	sprites[SPR_BOOMERANG] = new Sprite("Data\\Player\\Weapon\\boomerang.png", "Data\\Player\\Weapon\\boomerang.txt");
	sprites[SPR_HOLYWATER] = new Sprite("Data\\Player\\Weapon\\holy_water.png", "Data\\Player\\Weapon\\holy_water.txt");
	sprites[SPR_THROWING_AXE] = new Sprite("Data\\Player\\Weapon\\throwing_axe.png", "Data\\Player\\Weapon\\throwing_axe.txt");
	sprites[SPR_BRIDGE] = new Sprite("Data\\Bridge\\bridge.png", "Data\\Bridge\\bridge.txt");
}

SpriteManager::~SpriteManager()
{
	for (int i = 0; i < SPR_COUNT; i++)
	{
		if (sprites[i]->image != enemies)
			delete sprites[i]->image;

		delete[] sprites[i]->animates;
		delete sprites[i];
	}

	delete enemies;
}
