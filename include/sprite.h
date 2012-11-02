#ifndef SPRITE_H_
#define SPRITE_H_

#include <nds.h>
#include "entity.h"
#include "transformable.h"
#include "spritedata.h"

/**
 * A class that represents a renderable sprite on the screen.
 * The sprite can move around, and can be rendered
 * TODO: Make this an animated sprite
 */
class Sprite: public Entity, public Transformable {
	private:
		SpriteData* spriteData;
		int8 currentFrame;
		void boundFrameNumber(void);
		void copyToGfxBuffer(void);
	public:
		u8 spriteOffset;
		bool vflip;
		bool hflip;

		Sprite(SpriteData*);
		~Sprite(void);
		void nextFrame(void);
		void prevFrame(void);
		void setFrame(int8 givenFrame);
		int8 getFrame(void);
		void Render(void);
};

#endif
