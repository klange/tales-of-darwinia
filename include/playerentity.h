#ifndef PLAYER_ENTITY_H_
#define PLAYER_ENTITY_H_

#include "livingentity.h"
#include "inputmanager.h"
#include "itementity.h"

class PlayerEntity : public LivingEntity
{
public:
	virtual ~PlayerEntity();
	PlayerEntity(SpriteData* gfx);

	virtual void Update();

	void Collect(ItemEntity* item);
};

extern PlayerEntity* gpPlayerEntity;

#endif // PLAYER_ENTITY_H_
