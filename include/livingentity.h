#ifndef LIVING_ENTITY_H_
#define LIVING_ENTITY_H_

#include <nds.h>
#include "sprite.h"
#include "spritedata.h"
#include "livingstats.h"

enum {
	MOVING = 0,
	STOPPED = 1
};


class LivingEntity : public Sprite
{
public:
	LivingEntity(SpriteData *gfx) : Sprite(gfx) {
		mStats->health = 4; 
		mStats->attack = 1;
	}
	virtual void Damage(u16 damage);
	virtual void OnDeath() {};

	virtual void Update(void);
	void setTargetPosition(Vector3<s16>);
	Vector3<s16> getTargetPosition(void);

	LivingStats* mStats;

protected:
	Vector3<s16> targetPosition;
	float32 speed;
	float32 acceleration;
	float32 maxSpeed;
	u8 movementState;
};

#endif // LIVING_ENTITY_H_
