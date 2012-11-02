#ifndef PLAYER_ENTITY_H_
#define PLAYER_ENTITY_H_

#include "livingentity.h"

class PlayerEntity : public LivingEntity
{
public:
	PlayerEntity(SpriteData* gfx) : LivingEntity(gfx) {}
	virtual void Update();
};

#endif // PLAYER_ENTITY_H_
