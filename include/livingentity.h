#ifndef LIVING_ENTITY_H_
#define LIVING_ENTITY_H_

#include "sprite.h"
#include "spritedata.h"
#include "livingstats.h"

class LivingEntity : public Sprite
{
public:
	LivingEntity(SpriteData *gfx) : Sprite(gfx) {}

	virtual void Update(void);

protected:
	LivingStats mStats;
	Vector3<s16> targetPos;
};

#endif // LIVING_ENTITY_H_
