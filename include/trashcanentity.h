#ifndef TRASHCAN_ENTITY_H_
#define TRASHCAN_ENTITY_H_

#include "enemyentity.h"
#include "spritedata.h"

class TrashCanEntity : public EnemyEntity
{
public:
	TrashCanEntity(SpriteData* gfx, LivingStats* stats) : EnemyEntity(gfx, stats){}

	virtual void Update();
	
	// What else do we need?
};

#endif // TRASHCAN_ENTITY_H_
