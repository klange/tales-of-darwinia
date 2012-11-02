#ifndef PLAYER_ENTITY_H_
#define PLAYER_ENTITY_H_

#include "livingentity.h"
#include "inputmanager.h"
#include "itementity.h"

class PlayerEntity : public LivingEntity
{
public:
	PlayerEntity(SpriteData* gfx) : LivingEntity(gfx) {}
	virtual void Update(InputManager* inputManager);

	void Collect(ItemEntity* item);
};

#endif // PLAYER_ENTITY_H_
