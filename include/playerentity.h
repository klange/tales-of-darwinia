#ifndef PLAYER_ENTITY_H_
#define PLAYER_ENTITY_H_

#include "livingentity.h"
#include "inputmanager.h"
#include "itementity.h"

class PlayerEntity : public LivingEntity
{
public:
	virtual ~PlayerEntity();
	PlayerEntity(SpriteData* gfx, LivingStats* stats);

	virtual void Init();
	virtual void Update();

	void Collect(ItemEntity* item);

	void BlitStatus();

	virtual EntityType getType();
	virtual void OnDeath();
};

extern PlayerEntity* gpPlayerEntity;

#endif // PLAYER_ENTITY_H_
