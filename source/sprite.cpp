#include <nds.h>
#include "sprite.h"

void Sprite::draw(void) {
	oamSet(
		&oamSub,
		0, // oam index
		position.x(),
		position.y(),
		0, //z-index
		0, // palette index
		SpriteSize_16x16,
		SpriteColorFormat_256Color,
		gfx_data[currentFrame], // grahpics data
		-1, //rotation
		false, //double size when rotating
		hidden,
		false, //wflip
		false, //hflip
		false //mosaic?
	);
}

Sprite::Sprite(void) {
	gfx_data = NULL;
}

Sprite::Sprite(u16** in_gfx_data) {
	gfx_data = in_gfx_data;
}
