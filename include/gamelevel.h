#ifndef GAME_LEVEL_H_
#define GAME_LEVEL_H_


#include <nds.h>
#include "map_type.h"
#include "maps.h"
#include "itementity.h"

// NOTE: if you add a new type here, make sure you add to the corresponding mappings in gamelevel.cpp
typedef enum _EnemyType
{
	ENEMY_UNKNOWN,
	ENEMY_TRASH_CAN,
	ENEMY_EMPLOYEE,
} EnemyType;

class TilePosition
{
public:
	TilePosition(u16 x, u16 y);
	u16 pixelX();
	u16 pixelY();
	u16 x;
	u16 y;
};

class ItemSpecification
{
public:
	ItemSpecification(u16 x, u16 y, ItemType type);
	TilePosition* position;
	ItemType type;
};

class EnemySpecification
{
public:
	EnemySpecification(u16 x, u16 y, EnemyType type, ItemSpecification* rewards);
	TilePosition* position;
	EnemyType type;
	ItemSpecification* rewards;
};

class GameLevel
{
public:
	GameLevel(map_t* map, u16 playerX, u16 playerY, EnemySpecification** enemies, ItemSpecification** items, int music);
	map_t* map;
	TilePosition* playerPosition;
	EnemySpecification** enemies;
	ItemSpecification** items;
	int music;
};

class LevelLoader
{
public:
	MapEngine load(GameLevel* level);
};

extern LevelLoader levelLoader;

#endif // GAME_LEVEL_H_
