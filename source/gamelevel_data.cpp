#include "map_data.h"
#include "gamelevel_data.h"
#include "audiomanager.h"

EnemySpecification ENEMIES_ONE[] = {
	EnemySpecification(6, 4, ENEMY_EMPLOYEE)
};

ItemSpecification ITEMS_ONE[] = {

};

GameLevel GAME_LEVEL_ONE(
	map,
	3, 4,
	ENEMIES_ONE,
	ITEMS_ONE,
	MOD_TECHNO_MOZART
);

GameLevel GAME_LEVELS[] = {
	GAME_LEVEL_ONE
};
