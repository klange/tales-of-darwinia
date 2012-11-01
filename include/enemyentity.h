#ifndef ENEMY_ENTITY_H_
#define ENEMY_ENTITY_H_

#include "sprite.h"

class EnemyEntity : public Sprite
{
public:
    EnemyEntity(u16* gfx) : Sprite(gfx) {}
	virtual void Update();
};

#endif // ENEMY_ENTITY_H_
