#include <nds.h>
#include "sprite.h"
#include "spritedata.h"
#include <stdio.h>

void Sprite::draw(void) {
	iprintf("%d\n", hidden);
	oamSet(
		&oamSub,
		spriteData->oamIndex, // oam index
		position.x(),
		position.y(),
		spriteData->priority, // priority
		spriteData->paletteIndex,
		spriteData->spriteSize,
		spriteData->spriteColorFormat,
		spriteData->spriteGfxMem, // grahpics data
		-1, // affine transformation context
		false, //double size when rotating
		false, //hidden
		false, //wflip
		false, //hflip
		false //mosaic?
	);
}

Sprite::Sprite(SpriteData* inSpriteData) {
	spriteData = inSpriteData;
	dmaCopy(spriteData->spriteTilesMem, spriteData->spriteGfxMem, 32*32);
	currentFrame = 0;
}

void Sprite::nextFrame(void) {
	currentFrame++;
	if (currentFrame >= spriteData->maxNumFrames) {
		currentFrame = 0;
	}

	u8* offset = spriteData->spriteTilesMem + (currentFrame+1*spriteData->maxNumFrames) * 32*32;
	dmaCopy(offset, spriteData->spriteGfxMem, 32*32);
}
