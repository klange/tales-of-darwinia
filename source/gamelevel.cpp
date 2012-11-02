#include <nds.h>
#include <stdio.h>
#include "gamelevel.h"

// sprite resources
#include "darwin.h"
#include "man.h"

#include "sprite.h"
#include "spritedata.h"

// maps
#include "maps.h"
#include "map_data.h"

#include "playerentity.h"
#include "enemyentity.h"

#include "audiomanager.h"

LevelLoader levelLoader;

LivingStats DEFAULT_PLAYER_STATS(8, 8, 8, 8, 8);

// map from enemy type to sprite buffer
// NOTE: must parallel EnemyType order
u8* SPRITE_TILES_BY_ENEMY_TYPE[] = {
	NULL, // ENEMY_UNKNOWN
	(u8*) manTiles, // TODO: replace with trashCanTiles
	(u8*) manTiles,
	NULL,
};

// TODO: map from item type to sprite buffer
u8* SPRITE_TILES_BY_ITEM_TYPE[] = {
	NULL,
};

// map from EnemyType to stats
// NOTE: must parallel EnemyType order
LivingStats* STATS_BY_ENEMY_TYPE[] = {
	NULL, // ENEMY_UNKNOWN
	new LivingStats(8, 0, 0, 8, 8), // ENEMY_TRASH_CAN
	new LivingStats(8, 8, 8, 8, 16), // ENEMY_EMPLOYEE
	NULL
};

// TODO: map from ItemType to stats
LivingStats* STATS_BY_ITEM_TYPE[] = {

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

ItemSpecification::ItemSpecification(TilePosition* position, ItemType type)
{
	this->position = position;
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
		level->map
	);

	/* Load the relevant data into the VRAM */
	mapEngine.initVRAM(
		&BG_PALETTE_SUB[0],
		(u8*)BG_TILE_RAM_SUB(1),
		(u16*)BG_MAP_RAM_SUB(0)
	);

	/* Make the darwin sprite */
	SpriteData* gfx = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)darwinTiles, 3);
	dmaCopy(darwinPal, SPRITE_PALETTE_SUB, 512);

//	dmaCopy(manPal, SPRITE_PALETTE_SUB, 512);

	PlayerEntity* playerEntity = new PlayerEntity(gfx);
	playerEntity->Init();
	playerEntity->size = Vector3<s16>(16,16,0);
	playerEntity->setPosition(Vector3<s16>(level->playerPosition->pixelX(), level->playerPosition->pixelY(), 1));

	EnemySpecification** enemies = level->enemies;
	while (*enemies)
	{
		EnemySpecification* enemySpec = *enemies;
		SpriteData* enemySprite = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, SPRITE_TILES_BY_ENEMY_TYPE[enemySpec->type], 3);
		EnemyEntity* enemyEntity = new EnemyEntity(enemySprite);
		enemyEntity->Init();
		enemyEntity->size = Vector3<s16>(16,16,0);
		enemyEntity->setPosition(Vector3<s16>(enemySpec->position->pixelX(), enemySpec->position->pixelY(), 0));
		enemies++;
	}

	audioManager.playMusic(level->music);

	return mapEngine;
}
