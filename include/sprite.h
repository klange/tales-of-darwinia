#ifndef SPRITE_H_
#define SPRITE_H_

#include <nds.h>
#include "entity.h"
#include "renderable.h"
#include "transformable.h"

class Sprite: public IRenderable, public IEntity, public Transformable {
	public:
		u16* gfx_data;
		Sprite(void);
		Sprite(u16*);

		void draw(void);
};

#endif