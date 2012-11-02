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
	void setTargetPosition(Vector3<s16>);

protected:
	LivingStats mStats;
	Vector3<s16> targetPosition;
};

#endif // LIVING_ENTITY_H_
