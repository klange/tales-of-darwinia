#ifndef PLAYER_ENTITY_H_
#define PLAYER_ENTITY_H_

#include "sprite.h"

class PlayerEntity : public Sprite
{
public:
    PlayerEntity(u16* gfx) : Sprite(gfx) {}
	virtual void Update();
};

#endif // PLAYER_ENTITY_H_
