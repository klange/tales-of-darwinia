#include <nds.h>
#include "sprite.h"
#include "spritedata.h"
#include "inputmanager.h"
#include "playerentity.h"
#include "maps.h"
#include <stdio.h>


void Sprite::Render(void) {

	s16 drawX = position.x() + anchor.x();
	s16 drawY = position.y() + anchor.y();
	if(isScrollable)
	{
		s16 mapMinX = gpMapEngine->getScrollX();
		s16 mapMaxX = mapMinX + 255;
		s16 mapMinY = gpMapEngine->getScrollY();
		s16 mapMaxY = mapMinY + 255;
		if(drawX + 32 < mapMinX || drawX > mapMaxX || drawY + 32 < mapMinY || drawY > mapMaxY)
		{
			// force them off screen
			drawX = 256;
			drawY = 0;
		}
		else
		{
			drawX -= mapMinX;
			drawY -= mapMinY;
		}
	}

	oamSet(
		&oamSub,
		spriteData->oamIndex, // oam index
		drawX,
		drawY,
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
	isScrollable = true;

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
		// adjust screen space point to world space
		touchPos += Vector3<s16>((s16)gpMapEngine->getScrollX(), (s16)gpMapEngine->getScrollY(), 0);

		BoundingBox<s16> bb;
		getBoundingBox(bb);
		if (bb.PointInside(touchPos))
		{
			Vector3<s16> toPlayer = gpPlayerEntity->position - this->position;
			if (toPlayer.magnitude() < 45)
			{
				return true;
			}
		}
	}
	return false;
}
