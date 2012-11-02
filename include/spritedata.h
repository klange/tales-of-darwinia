#ifndef SPRITEDATA_H_
#define SPRITEDATA_H_

#include <nds.h>

class SpriteData {
	private:
		static bool oamAllocationTable[SPRITE_COUNT];
		void assignOamIndex(void);

	public:
		u16* spriteGfxMem;
		u8* spriteTilesMem;
		s16 transformContext;

		u8 maxNumFrames;

		u8 priority;
		u8 oamIndex;
		u8 paletteIndex;
		SpriteSize spriteSize;
		SpriteColorFormat spriteColorFormat;

		/**
		 * SpriteSize - the size of the sprite
		 * SpriteColorFormat - the format of the sprite
		 * spriteTiles - the sprite tiles image
		 */
		SpriteData(SpriteSize size, SpriteColorFormat format, u8* spriteTiles, u8);
		~SpriteData(void);
};

#endif
