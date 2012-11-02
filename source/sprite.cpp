#include <nds.h>
#include "sprite.h"
#include "spritedata.h"
#include "inputmanager.h"
#include "playerentity.h"
#include <stdio.h>


void Sprite::Render(void) {
	oamSet(
		&oamSub,
		spriteData->oamIndex, // oam index
		position.x() + anchor.x(),
		position.y() + anchor.y(),
		spriteData->priority, // priority
		spriteData->paletteIndex, // palette index
		spriteData->spriteSize,
		spriteData->spriteColorFormat,
		spriteData->spriteGfxMem, // grahpics data
		transformContext, // affine transformation context
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
	updateCount = 0;
	spriteOffset = 0;
	transformContext = -1;
	vflip = false;
	hflip = false;
	anchor = Vector3<s16>(-16, -16, 0);
	isAnimated = true;

	copyToGfxBuffer();
}

Sprite::~Sprite(void) {
	delete spriteData;
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
  if (isAnimated) {
	currentFrame++;
	boundFrameNumber();
	copyToGfxBuffer();
  }
}

void Sprite::prevFrame(void) {
  if (isAnimated) {
	currentFrame--;
	boundFrameNumber();
	copyToGfxBuffer();
  }
}

void Sprite::setFrame(int8 givenFrame) {
	currentFrame = givenFrame;
	boundFrameNumber();
	copyToGfxBuffer();
}

void Sprite::Update(void) {
	updateCount++;
}

int8 Sprite::getFrame(void) {
  	return currentFrame;
}

/**
 * Helper that an entity's Update method can use to check if we are being touched
 *
 * TODO: move this to a GameEntity that both LivingEntity and ItemEntity inherit from.
 * Such a GameEntity would be a Sprite.
 */
bool Sprite::IsTouchedByNearbyPlayer()
{
	Vector3<s16> touchPos;
	if(gInputManager.getCurrentTouchPosition(touchPos))
	{
		BoundingBox<s16> bb;
		getBoundingBox(bb);
		if (bb.PointInside(touchPos))
		{
			Vector3<s16> toPlayer = gpPlayerEntity->position - this->position;
			if (toPlayer.magnitude() < 32)
			{
				return true;
			}
		}
	}
	return false;
}
