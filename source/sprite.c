#include <nds.h>
#include "sprite.h"

void drawSprite(Sprite* sprite) {
		Position location;
		location.x = sprite->pos.x - sprite->anchorOffset.x;
		location.y = sprite->pos.y - sprite->anchorOffset.y;
		u16* gfx_buffer = sprite->gfx_buffer;

		oamSet(
			&oamSub,
			0, // oam index
			location.x, // x location of sprite
			location.y, // y location of sprite
			0, // z-index
			0, // palette index (i have no clue wtf this does)
			SpriteSize_16x16,
			SpriteColorFormat_256Color,
			gfx_buffer, // pointer to the actualy graphic
			-1, // rotation
			false, // double the size when rotating?
			false, // hide?
			false, // vflip
			false, // hflip
			false //apply mosaic, what does this do?
		);
}
