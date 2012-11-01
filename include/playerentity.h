#ifndef PLAYER_ENTITY_H_
#define PLAYER_ENTITY_H_

#include "livingentity.h"

class PlayerEntity : public LivingEntity
{
public:
    PlayerEntity(u16* gfx) : LivingEntity(gfx) {}
	virtual void Update();
};

#endif // PLAYER_ENTITY_H_
