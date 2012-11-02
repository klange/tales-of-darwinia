#include <nds.h>
#include "spritedata.h"

bool SpriteData::oamAllocationTable[SPRITE_COUNT];

SpriteData::SpriteData(SpriteSize size, SpriteColorFormat format, u8* spriteTiles, u8 numFrames) {
	spriteSize = size;
	spriteColorFormat = format;
	priority = 0;
	spriteGfxMem = oamAllocateGfx(&oamSub, spriteSize, spriteColorFormat);
	spriteTilesMem = (u8*)spriteTiles;
	maxNumFrames = numFrames;

	assignOamIndex();
}

void SpriteData::assignOamIndex(void) {
	for (int lcv = 0; lcv < SPRITE_COUNT; lcv++) {
		if (oamAllocationTable[lcv] == false) {
			oamIndex = lcv;
			oamAllocationTable[lcv] = true;
			break;
		}
	}
}

SpriteData::~SpriteData() {
	oamClearSprite(&oamSub, oamIndex);
	oamFreeGfx(&oamSub, spriteGfxMem);
	oamUpdate(&oamSub);
	oamAllocationTable[oamIndex] = false;
}
