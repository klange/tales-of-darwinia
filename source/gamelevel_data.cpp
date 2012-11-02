#include "map_data.h"
#include "gamelevel_data.h"
#include "audiomanager.h"

EnemySpecification* ENEMIES_ONE[] = {
	new EnemySpecification(10, 6, ENEMY_EMPLOYEE, NULL),
	NULL
};

ItemSpecification* ITEMS_ONE[] = {
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
