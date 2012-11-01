#ifndef PLAYER_ENTITY_H_
#define PLAYER_ENTITY_H_

#include "sprite.h"
#include "inputmanager.h"

class PlayerEntity : public Sprite
{
public:
    PlayerEntity(u16* gfx) : Sprite(gfx) {}
	virtual void Update(InputManager* inputManager);
};

#endif // PLAYER_ENTITY_H_
