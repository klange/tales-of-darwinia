#include <nds.h>
#include <stdio.h>
#include "gamelevel.h"

// sprite resources
#include "darwin.h"
#include "man.h"
#include "trashcan.h"
#include "peanut_butter.h"

#include "sprite.h"
#include "spritedata.h"

// maps
#include "maps.h"
#include "map_data.h"

#include "playerentity.h"
#include "enemyentity.h"
#include "trashcanentity.h"
#include "itementity.h"

#include "audiomanager.h"

LevelLoader levelLoader;

LivingStats DEFAULT_PLAYER_STATS(100, 2, 1, 100, 0);

// map from enemy type to sprite buffer
// NOTE: must parallel EnemyType order
u8* SPRITE_TILES_BY_ENEMY_TYPE[] = {
	NULL, // ENEMY_UNKNOWN
	(u8*) trashcanTiles,
	(u8*) manTiles,
	NULL,
};

u8 SPRITE_FRAMES_BY_ENEMY_TYPE[] = {
	0, // ENEMY_UNKNOWN
	0,
	3,
};
//  map from item type to sprite buffer
u8* SPRITE_TILES_BY_ITEM_TYPE[] = {
	NULL, // ITEM_UNKNOWN
	(u8*) peanut_butterTiles,
	(u8*) peanut_butterTiles,
	(u8*) peanut_butterTiles,
	NULL,
};

// HEALTH, ATTACK, SPEED, MAXHEALTH, POINTS

// map from EnemyType to stats
// NOTE: must parallel EnemyType order
LivingStats* STATS_BY_ENEMY_TYPE[] = {
	NULL, // ENEMY_UNKNOWN
	new LivingStats(8, 0, 0, 8, 50), // ENEMY_TRASH_CAN
	new LivingStats(8, 8, 8, 8, 100), // ENEMY_EMPLOYEE
	NULL,
};

// map from ItemType to stats
// NOTE: must parallel ItemType order
LivingStats* STATS_BY_ITEM_TYPE[] = {
	NULL, // UNKNOWN
	new LivingStats(4, 16, 0, 0, 50), // PEANUT_BUTTER
	new LivingStats(-50, -50, 0, 0, -500), // CHOCOLATE
	new LivingStats(8, 8, 0, 0, 15), // DRUMSTICK
	NULL,
};


TilePosition::TilePosition(u16 x, u16 y)
{
	this->x = x;
	this->y = y;
}

u16 TilePosition::pixelX()
{
	return this->x * 16;
}

u16 TilePosition::pixelY()
{
	return this->y * 16;
}

EnemySpecification::EnemySpecification(u16 x, u16 y, EnemyType type, ItemSpecification* rewards)
{
	this->position = new TilePosition(x, y);
	this->type = type;
	this->rewards = rewards;
}

ItemSpecification::ItemSpecification(u16 x, u16 y, ItemType type)
{
	this->position = new TilePosition(x, y);
	this->type = type;
}

GameLevel::GameLevel(map_t* map, u16 playerX, u16 playerY, EnemySpecification** enemies, ItemSpecification** items, int music)
{
	this->map = map;
	this->playerPosition = new TilePosition(playerX, playerY);
	this->enemies = enemies;
	this->items = items;
	this->music = music;
}

MapEngine LevelLoader::load(GameLevel* level)
{
	/* Load data from map_data.h into the map engine */
	MapEngine mapEngine = MapEngine(
		&tile_palette,
		&tile_set,
		level->map,
		&nowalk
	);

	/* Load the relevant data into the VRAM */
	mapEngine.initVRAM(
		&BG_PALETTE_SUB[0],
		(u8*)BG_TILE_RAM_SUB(1),
		(u16*)BG_MAP_RAM_SUB(0)
	);

	/* Make the darwin sprite */
	SpriteData* gfx = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)darwinTiles, 3);
	dmaCopy(darwinPal, &SPRITE_PALETTE_SUB[0], 512);
	gfx->paletteIndex = 0;

	PlayerEntity* playerEntity = new PlayerEntity(gfx, &DEFAULT_PLAYER_STATS);
	playerEntity->Init();
	playerEntity->size = Vector3<s16>(32,32,0);
	playerEntity->setPosition(Vector3<s16>(level->playerPosition->pixelX(), level->playerPosition->pixelY(), 1));
	playerEntity->setTargetPosition(Vector3<s16>(level->playerPosition->pixelX(), level->playerPosition->pixelY(), 1));

	EnemySpecification** enemies = level->enemies;
	while (*enemies)
	{
		EnemySpecification* spec = *enemies;
		SpriteData* sprite = new SpriteData(
			SpriteSize_32x32,
			SpriteColorFormat_256Color,
			SPRITE_TILES_BY_ENEMY_TYPE[spec->type],
			SPRITE_FRAMES_BY_ENEMY_TYPE[spec->type]
		);
		sprite->paletteIndex=1;
		EnemyEntity* entity;
		if (spec->type == ENEMY_TRASH_CAN){
			entity = new TrashCanEntity(sprite, STATS_BY_ENEMY_TYPE[spec->type]);
		} else {
			entity = new EnemyEntity(sprite, STATS_BY_ENEMY_TYPE[spec->type]);
		}		
		entity->Init();
		entity->size = Vector3<s16>(32,32,0);
		entity->setPosition(Vector3<s16>(spec->position->pixelX(), spec->position->pixelY(), 0));
		enemies++;
	}
	dmaCopy(manPal, &SPRITE_PALETTE_SUB[8], 512);

	ItemSpecification** items = level->items;
	while (*items)
	{
		ItemSpecification* spec = *items;
		SpriteData* sprite = new SpriteData(
			SpriteSize_32x32,
			SpriteColorFormat_256Color,
			SPRITE_TILES_BY_ITEM_TYPE[spec->type],
			0 // all items are single-frame
		);
		sprite->paletteIndex=0;
		ItemEntity* entity = new ItemEntity(sprite, STATS_BY_ITEM_TYPE[spec->type], spec->type);
		entity->Init();
		entity->size = Vector3<s16>(32,32,0);
		entity->setPosition(Vector3<s16>(spec->position->pixelX(), spec->position->pixelY(), 0));
		items++;
	}

	playerEntity->BlitStatus();

	audioManager.playMusic(level->music);

	return mapEngine;
}
