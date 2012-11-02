#ifndef PLAYER_ENTITY_H_
#define PLAYER_ENTITY_H_

#include "livingentity.h"

class PlayerEntity : public LivingEntity
{
public:
	virtual ~PlayerEntity();
	PlayerEntity(SpriteData* gfx);

	virtual void Update();
};

extern PlayerEntity* gpPlayerEntity;

#endif // PLAYER_ENTITY_H_
