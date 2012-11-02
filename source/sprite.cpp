#include <nds.h>
#include "sprite.h"


int Sprite::sNextIndex = 0; // the next sprite index to be allocated

void Sprite::draw(void) {
	oamSet(
		&oamSub,
		mIndex, // oam index
		position.x(),
		position.y(),
		0, //z-index
		0, // palette index
		SpriteSize_16x16,
		SpriteColorFormat_256Color,
		gfx_data, // grahpics data
		-1, //rotation
		false, //double size when rotating
		hidden,
		false, //wflip
		false, //hflip
		false //mosaic?
	);
}

void Sprite::Render()
{
	doRender(NULL);
}

Sprite::Sprite(u16* in_gfx_data) {
	mIndex = sNextIndex++; // this is ghetto, and has danger of overflowing
	gfx_data = in_gfx_data;
}
