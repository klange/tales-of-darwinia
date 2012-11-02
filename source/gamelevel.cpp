#include "gamelevel.h"


// TODO: map from enemy type to sprite buffer

// TODO: map from item type to sprite buffer


TilePosition::TilePosition(u16 x, u16 y)
{
	this->x = x;
	this->y = y;
}

EnemySpecification::EnemySpecification(u16 x, u16 y, EnemyType type)
{
	this->position = new TilePosition(x, y);
	this->type = type;
}

ItemSpecification::ItemSpecification(TilePosition* position, ItemType type)
{
	this->position = position;
	this->type = type;
}

GameLevel::GameLevel(u16* map, u16 playerX, u16 playerY, EnemySpecification* enemies, ItemSpecification* items, int music)
{
	this->map = map;
	this->playerPosition = new TilePosition(playerX, playerY);
	this->enemies = enemies;
	this->items = items;
	this->music = music;
}

void LevelLoader::load(GameLevel* level)
{

}
