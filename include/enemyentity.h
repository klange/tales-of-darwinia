#ifndef ENEMY_ENTITY_H_
#define ENEMY_ENTITY_H_

#include "livingentity.h"

class EnemyEntity : public LivingEntity
{
public:
    EnemyEntity(u16* gfx) : LivingEntity(gfx) {}
	virtual void Update();
};

#endif // ENEMY_ENTITY_H_
