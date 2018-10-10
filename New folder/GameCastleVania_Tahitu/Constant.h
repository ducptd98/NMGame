#pragma once
#define CLASS_NAME "CastleGame"
#define TITLE_STR "Game Castle Vania"

#define ANIMATE_DELAY_TIME_DEFAULT 0.1
#define SIMON_GO_STAIR_TIME 0.2
#define SCREEN_WIDTH		640
#define SCREEN_HEIGHT		480
#define X_MAP				-1791
#define Y_MAP				-526
#define VIEWPORT_WIDTH		256
#define VIEWPORT_HEIGHT		224
#define BACK_WIDTH			VIEWPORT_WIDTH
#define BACK_HEIGHT			VIEWPORT_HEIGHT
#define GRAVITY				300
#define ENEMY_VX_GO			40
#define SIMON_VX_GO			50
#define LIFE				8

#define WINDOW				WindowGame::getInstance()
#define GRAPHICS			Graphics::getInstance()
#define SIMON				Simon::getInstance()
#define SPRITEMANAGER		SpriteManager::getInstance()
#define CURSCENE			CastleVaniaScene::curScene
#define KEYBOARD			Keyboard::getInstance()
#define KEY					KeyGame::getInstance()
#define GAME_TIME			GameTime::getInstance()
#define COLLISION			CollisionManager::getInstance()
#define CAMERA				Camera::getInstance()
#define WEAPONLOCATION		WeaponLocations::getInstance()
#define WHIP				Whip::getInstance()
#define WHIPSITDOWN			WhipSitDown::getInstance()
#define STOPWATCH			StopWatch::getInstance()
#define TIME				GameTime::getInstance()->frameTime
#define GAMESOUND			GameSound::getInstance()

#define MAX(a,b)			a > b ? a : b
#define MIN(a,b)			a > b ? b : a

#define FRAME_RATE			(80.0f)
#define MIN_FRAME_RATE		(60.0f)
#define MIN_FRAME_TIME		(1.0f/FRAME_RATE)
#define MAX_FRAME_TIME		(1.0f/MIN_FRAME_RATE)

#define PI					3.14159265

#define AUDIO_FORMAT_TAG		WAVE_FORMAT_PCM
#define	AUDIO_NUM_OF_CHANNEL	2
#define AUDIO_SAMPLE_SPEED		22050
#define AUDIO_BITS_PER_SAMPLE	16
#define AUDIO_FLAGS				0
#define AUDIO_BUFFER_SIZE		640000
#define AUDIO_GUID				GUID_NULL
#define AUDIO_BLOCK_ALIGN(bitPerSample, nChannels)		(WORD)(bitPerSample / 8 * nChannels)
#define AUDIO_AVERAGE_BPS(samplesPerSec, blockAlign)	(DWORD)(samplesPerSec * blockAlign)

#define UP												"Data\\sound\\UP.wav"
#define ACID_RAIN_DROP									"Data\\sound\\AcidRainDrop.wav"
#define ALUCARD_BAT_CHANGE1								"Data\\sound\\AlucardBatChange1.wav"
#define ALUCARD_BAT_CHANGE2								"Data\\sound\\AlucardBatChange2.wav"
#define ALUCARD_HIT										"Data\\sound\\AlucardHit.wav"
#define AXE_TOSS										"Data\\sound\\AxeToss.wav"
#define BALLOF_DESTRUCTION								"Data\\sound\\BallofDestruction.wav"
#define BAT_SPLASH										"Data\\sound\\BatSplash.wav"
#define BLOCK_FALL1										"Data\\sound\\BlockFall1.wav"
#define BLOCK_FALL2										"Data\\sound\\BlockFall2.wav"
#define BONUS_BAG										"Data\\sound\\BonusBag.wav"
#define CHING1											"Data\\sound\\Ching1.wav"
#define CHING_MULTI										"Data\\sound\\ChingMulti.wav"
#define DAGGER_THROW									"Data\\sound\\DaggerThrow.wav"
#define DEATH											"Data\\sound\\Death.wav"
#define ENEMY_HIT1										"Data\\sound\\EnemyHit1.wav"
#define ENEMY_HIT2										"Data\\sound\\EnemyHit2.wav"
#define ENEMY_HIT3										"Data\\sound\\EnemyHit3.wav"
#define ENEMY_OW_WITH_GROWL								"Data\\sound\\EnemyOwWithGrowl.wav"
#define ENEGRY_RESTORE									"Data\\sound\\EnergyRestore.wav"
#define HARD_LANDING									"Data\\sound\\HardLanding.wav"
#define HEART											"Data\\sound\\Heart.wav"
#define HOLY_WATER										"Data\\sound\\Holywater.wav"
#define HOLY_WATER1										"Data\\sound\\Holywater1.wav"
#define KILL											"Data\\sound\\Kill.wav"
#define MAP_TREMORS										"Data\\sound\\MapTremors.wav"
#define PARTNER_PIRIT_APPEARS							"Data\\sound\\PartnerPiritAppears.wav"
#define PARTNER_SPIRIT_CHANGE							"Data\\sound\\PartnerSpiritChange.wav"
#define PAUSE_GAME										"Data\\sound\\PauseGame.wav"
#define POINT_RACKUP									"Data\\sound\\PointRackup.wav"
#define ROCK_CRACKIN									"Data\\sound\\RockCrackin.wav"
#define ROCK_CRACKS										"Data\\sound\\RockCracks.wav"
#define ROCK_CRACK_AND_FALLS							"Data\\sound\\RockCracksandFalls.wav"
#define ROCKY_RATTLE									"Data\\sound\\RockyRattle.wav"
#define ROSARY											"Data\\sound\\Rosary.wav"
#define SKELETON_KILL									"Data\\sound\\SkeletonKill.wav"
#define SPIDERLING										"Data\\sound\\Spiderling.wav"
#define STAGE_CLEAR										"Data\\sound\\StageClear.wav"
#define TIME_BONUS_POINT								"Data\\sound\\TimeBonusPoint.wav"
#define TIME_STOPPER									"Data\\sound\\TimeStopper.wav"
#define TITLE_SCREEN_THUNDER							"Data\\sound\\TitleScreenThunder.wav"
#define TREVOR_HIT										"Data\\sound\\TrevorHit.wav"
#define WALKING											"Data\\sound\\Walking.wav"
#define WHIP_SOUND										"Data\\sound\\Whip.wav"
#define WHIP_AND_KILL									"Data\\sound\\WhipandKill.wav"
#define WHIP_AND_ROCK_BREAKING							"Data\\sound\\WhipandRockBreaking.wav"
#define WHIP_AND_SKELETON								"Data\\sound\\WhipandSkeleton.wav"
#define WHIP_POWERUP_AND_WEAPONGET						"Data\\sound\\WhipPowerupandWeaponGet.wav"
#define PHONG_PHI_TIEU									"Data\\sound\\PhongPhiTieu.wav"
#define PHONG_DAO										"Data\\sound\\PhongDao.wav"
#define MUSIC_BATTLE_BOSS								"Data\\sound\\MusicBattleBoss.wav"
#define INTRO_GAME										"Data\\sound\\IntroGame.wav"
#define MUSIC_LEVEL2									"Data\\sound\\MusicLevel2.wav"
#define MUSIC_LEVEL3									"Data\\sound\\MusicLevel3.wav"
#define MUSIC_WIN_BOSS									"Data\\sound\\MusicWinBoss.wav"

//-------------------------- Enemies Minh Trang
#define MEDUSAHEADS			MedusaHead_List::getListMedusaHead_List()
#define BOOMERANG			Boomerang::getBoomerangs()
#define BONETOWER_BULLET	BoneTower_Bullet::getListBoneTower_Bullet()
#define	MEDUSA_SNAKE		Medusa_Snake::getListMedusa_Snake()
#define	MUMMYMAN_BANDAGE	MummyMan_Bandage::getListMummyMan_Bandage()
#define	SKELETON_BONE		Skeleton_Bone::getListSkeleton_Bone()
