#include <nds.h>
#include "sprite.h"
#include "spritedata.h"
#include <stdio.h>


void Sprite::draw(void) {
<<<<<<< HEAD
=======
	iprintf("   \x1b[32;1m%d\x1b[39m\n", currentFrame);
>>>>>>> 7c4585946c4982177825c420d66b79210e5c4af3
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
		vflip, //vflip
		hflip, //hflip
		false //mosaic?
	);
}

Sprite::Sprite(SpriteData* inSpriteData) {
	spriteData = inSpriteData;
	currentFrame = 0;
	vflip = false;
	hflip = false;

	copyToGfxBuffer();
}

void Sprite::boundFrameNumber(void) {
	if (currentFrame >= spriteData->maxNumFrames) {
		currentFrame = 0;
	}
	if (currentFrame < 0) {
		currentFrame = spriteData->maxNumFrames - 1;
	}
}

void Sprite::copyToGfxBuffer(void) {
	u8* offset = spriteData->spriteTilesMem + (currentFrame+1*spriteData->maxNumFrames) * 32*32;
	dmaCopy(offset, spriteData->spriteGfxMem, 32*32);
}

void Sprite::nextFrame(void) {
	currentFrame++;
	boundFrameNumber();
	copyToGfxBuffer();
}

void Sprite::prevFrame(void) {
	currentFrame--;
	boundFrameNumber();
	copyToGfxBuffer();
}

void Sprite::Render(void) {
	draw();
}

