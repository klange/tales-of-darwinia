#include "map_data.h"
#include "gamelevel_data.h"
#include "audiomanager.h"

EnemySpecification* ENEMIES_ONE[] = {
	new EnemySpecification(3, 3, ENEMY_TRASH_CAN, NULL),
	new EnemySpecification(6, 8, ENEMY_TRASH_CAN, NULL),
	new EnemySpecification(10, 6, ENEMY_EMPLOYEE, NULL),
	new EnemySpecification(5, 5, ENEMY_EMPLOYEE, NULL),
	NULL
};

ItemSpecification* ITEMS_ONE[] = {
	new ItemSpecification(10, 10, ITEM_PEANUT_BUTTER),
	new ItemSpecification(1, 1, ITEM_CHOCOLATE),
	new ItemSpecification(12, 3, ITEM_CHOCOLATE),
	NULL,
};

GameLevel* GAME_LEVEL_ONE = new GameLevel(
	&map,
	3, 6,
	ENEMIES_ONE,
	ITEMS_ONE,
	MOD_TECHNO_MOZART
);

GameLevel* GAME_LEVELS[] = {
	GAME_LEVEL_ONE,
	NULL
};
