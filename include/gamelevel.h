#ifndef GAME_LEVEL_H_
#define GAME_LEVEL_H_


#include <nds.h>
#include "map_type.h"


typedef enum _EnemyType
{
	ENEMY_UNKNOWN,
	ENEMY_TRASH_CAN,
	ENEMY_EMPLOYEE,
} EnemyType;

typedef enum _ItemType
{
	ITEM_UNKNOWN,
	ITEM_CHOCOLATE,
	ITEM_PEANUT_BUTTER,
	ITEM_KIBBLE,
	ITEM_BIT,
	ITEM_BONE,
	ITEM_CAT,
} ItemType;

class TilePosition
{
public:
	TilePosition(u16 x, u16 y);
	u16 x;
	u16 y;
};

class ItemSpecification
{
public:
	ItemSpecification(TilePosition* position, ItemType type);
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
	GameLevel(map_t* map, u16 playerX, u16 playerY, EnemySpecification* enemies, ItemSpecification* items, int music);
	map_t* map;
	TilePosition* playerPosition;
	EnemySpecification* enemies;
	ItemSpecification* items;
	int music;
};

class LevelLoader
{
public:
	void load(GameLevel* level);
};

extern LevelLoader levelLoader;

#endif // GAME_LEVEL_H_
