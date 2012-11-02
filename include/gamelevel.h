#ifndef GAME_LEVEL_H_
#define GAME_LEVEL_H_


#include <nds.h>


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

class EnemySpecification
{
public:
	EnemySpecification(u16 x, u16 y, EnemyType type);
	TilePosition* position;
	EnemyType type;
};

class ItemSpecification
{
public:
	ItemSpecification(TilePosition* position, ItemType type);
	TilePosition* position;
	ItemType type;
};

class GameLevel
{
public:
	GameLevel(u16* map, u16 playerX, u16 playerY, EnemySpecification* enemies, ItemSpecification* items, int music);
private:
	u16* map;
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

#endif // GAME_LEVEL_H_
