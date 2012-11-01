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
	loadGfx(in_gfx_data, 1);
	currentFrame = 0;
}

Sprite::Sprite(u16** in_gfx_data, u8 in_max_frames) {
	loadGfx(in_gfx_data, in_max_frames);
	currentFrame = 0;
}

void Sprite::loadGfx(u16** in_gfx_data, u8 in_max_frames) {
	gfx_data = in_gfx_data;
	max_frames = in_max_frames;
}

void Sprite::nextFrame(void) {
	currentFrame++;
	if (currentFrame > max_frames) {
		currentFrame = 0;
	}
}
