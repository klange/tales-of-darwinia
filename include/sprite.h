#ifndef SPRITE_H_
#define SPRITE_H_

#include <nds.h>
#include "entity.h"
#include "renderable.h"
#include "transformable.h"
#include "spritedata.h"

/**
 * A class that represents a renderable sprite on the screen.
 * The sprite can move around, and can be rendered
 * TODO: Make this an animated sprite
 */
class Sprite: public Renderable, public Entity, public Transformable {
	private:
		void draw(void);
		SpriteData* spriteData;
		u8 currentFrame;
	public:
		/* An array of pointers that points to locations in memory where sprite frames are */
		Sprite(SpriteData*);
		void nextFrame(void);
};

#endif