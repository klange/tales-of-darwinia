#include <nds.h>
#include "spritedata.h"

SpriteData::SpriteData(SpriteSize size, SpriteColorFormat format, u8* spriteTiles, u8 numFrames) {
	spriteSize = size;
	spriteColorFormat = format;
	oamIndex = 0;
	priority = 0;
	spriteGfxMem = oamAllocateGfx(&oamSub, spriteSize, spriteColorFormat);
	spriteTilesMem = (u8*)spriteTiles;
	maxNumFrames = numFrames;
}

SpriteData::~SpriteData() {
	oamFreeGfx(&oamSub, spriteGfxMem);
}
