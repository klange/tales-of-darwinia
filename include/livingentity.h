#ifndef LIVING_ENTITY_H_
#define LIVING_ENTITY_H_

#include "sprite.h"
#include "livingstats.h"

class LivingEntity : public Sprite
{
public:
	LivingEntity(u16 *gfx) : Sprite(gfx) {}
	virtual void Update() = 0;

protected:
	LivingStats mStats;
};

#endif // LIVING_ENTITY_H_
