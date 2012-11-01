#ifndef SPRITE_H_
#define SPRITE_H_

#include <nds.h>
#include "entity.h"
#include "renderable.h"
#include "transformable.h"

/**
 * A class that represents a renderable sprite on the screen.
 * The sprite can move around, and can be rendered
 * TODO: Make this an animated sprite
 */
class Sprite: public Renderable, public Entity, public Transformable {
	private:
		void draw(void);
		u16** gfx_data;
		u8 currentFrame;
		u8 max_frames;
	public:
		/* An array of pointers that points to locations in memory where sprite frames are */
		Sprite(void);
		Sprite(u16**);
		Sprite(u16**, u8);
		void loadGfx(u16**, u8);
		void nextFrame(void);
};

#endif