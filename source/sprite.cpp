#include <nds.h>
#include "sprite.h"
#include "spritedata.h"
#include <stdio.h>


void Sprite::Render(void) {
	if(hidden)
		printf("LOL IM HERE");

	oamSet(
		&oamSub,
		spriteData->oamIndex, // oam index
		position.x() + anchor.x(),
		position.y() + anchor.y(),
		spriteData->priority, // priority
		spriteData->paletteIndex,
		spriteData->spriteSize,
		spriteData->spriteColorFormat,
		spriteData->spriteGfxMem, // grahpics data
		-1, // affine transformation context
		false, //double size when rotating
		hidden, //hidden
		vflip, //vflip
		hflip, //hflip
		false //mosaic?
	);
}

Sprite::Sprite(SpriteData* inSpriteData) {
	spriteData = inSpriteData;
	currentFrame = 0;
	spriteOffset = 0;
	vflip = false;
	hflip = false;
	anchor = Vector3<s16>(-16, -16, 0);

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
	u8* offset = spriteData->spriteTilesMem + (currentFrame+spriteOffset*spriteData->maxNumFrames) * 32*32;
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

void Sprite::setFrame(int8 givenFrame) {
	currentFrame = givenFrame;
	boundFrameNumber();
	copyToGfxBuffer();
}

int8 Sprite::getFrame(void) {
  	return currentFrame;
}

