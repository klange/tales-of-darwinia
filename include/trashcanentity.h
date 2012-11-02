#ifndef TRASHCAN_ENTITY_H_
#define TRASHCAN_ENTITY_H_

#include "enemyentity.h"
#include "spritedata.h"

class TrashCanEntity : public EnemyEntity
{
public:
	TrashCanEntity(SpriteData* gfx) : EnemyEntity(gfx){}

	virtual void Update();
	
	// What else do we need?
};

#endif // TRASHCAN_ENTITY_H_
