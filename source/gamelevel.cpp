#include "gamelevel.h"


// TODO: map from enemy type to sprite buffer

// TODO: map from item type to sprite buffer


TilePosition::TilePosition(u16 x, u16 y)
{
	this->x = x;
	this->y = y;
}

EnemySpecification::EnemySpecification(TilePosition* position, EnemyType type)
{
	this->position = position;
	this->type = type;
}

ItemSpecification::ItemSpecification(TilePosition* position, ItemType type)
{
	this->position = position;
	this->type = type;
}

GameLevel::GameLevel(u16* map, TilePosition* playerPosition, EnemySpecification** enemies, ItemSpecification** items, int music)
{
	this->map = map;
	this->playerPosition = playerPosition;
	this->enemies = enemies;
	this->items = items;
	this->music = music;
}

void LevelLoader::load(GameLevel* level)
{

}
