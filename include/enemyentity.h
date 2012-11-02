#ifndef ENEMY_ENTITY_H_
#define ENEMY_ENTITY_H_

#include "livingentity.h"
#include "spritedata.h"

class EnemyEntity : public LivingEntity
{
public:
   EnemyEntity(SpriteData* gfx) : LivingEntity(gfx) {}
	virtual void Update();
	virtual void OnDeath();
};

#endif // ENEMY_ENTITY_H_
