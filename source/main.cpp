/* vim: ts=4 sw=4 noexpandtab
 * Tales of Darwinia
 *
 * A Game by Yelp Engineers
 *
 * Henri B
 * Paul B
 * Patrick T
 * Kevin L
 * Jeryl C
 * Mike G
 * MAYBE YOU!
 *
 */

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "darwin.h"

#include "sprite.h"
#include "spritedata.h"

int main(void) {
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	SpriteData* darwinSpriteData = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)darwinTiles, 3);
	Sprite* darwinSprite = new Sprite(darwinSpriteData);

	dmaCopy(darwinPal, SPRITE_PALETTE_SUB, 512);
	//consoleDemoInit();

	int lolcounter = 0;
	while(1) {

		oamUpdate(&oamSub);
		swiWaitForVBlank();

		lolcounter++;
		if (lolcounter >= 10) {
			darwinSprite->draw();
			darwinSprite->prevFrame();
			lolcounter = 0;
		}
	}

	return 0;
}
