#ifndef LIVING_ENTITY_H_
#define LIVING_ENTITY_H_

#include "sprite.h"
#include "spritedata.h"
#include "livingstats.h"

class LivingEntity : public Sprite
{
public:
	LivingEntity(SpriteData *gfx) : Sprite(gfx) {
		mStats.health = 4; 
		mStats.attack = 1;
	}
	virtual void Damage(u16 damage);
	virtual void OnDeath() {};

	LivingStats mStats;
};

#endif // LIVING_ENTITY_H_
