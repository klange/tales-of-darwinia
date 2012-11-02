#ifndef PLAYER_ENTITY_H_
#define PLAYER_ENTITY_H_

#include "livingentity.h"
#include "inputmanager.h"

class PlayerEntity : public LivingEntity
{
public:
	PlayerEntity(SpriteData* gfx) : LivingEntity(gfx) {}
	virtual void Update(InputManager* inputManager);
};

#endif // PLAYER_ENTITY_H_
