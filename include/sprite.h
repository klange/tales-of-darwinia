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
		SpriteData* spriteData;
		int8 currentFrame;
		void boundFrameNumber(void);
		void copyToGfxBuffer(void);
	public:
		bool vflip;
		bool hflip;

		Sprite(SpriteData*);
		void nextFrame(void);
		void prevFrame(void);
		void draw(void);
};

#endif