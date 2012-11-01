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
		int mIndex; // which sprite am I?
		static int sNextIndex; // the next sprite index to be allocated
	public:
		u16* gfx_data;
		Sprite(u16* gfx = NULL);

		virtual void Render();
};

#endif
