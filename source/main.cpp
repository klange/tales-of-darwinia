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

#include "man.h"

#include "sprite.h"
#include "spritedata.h"

int main(void) {
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	SpriteData* manSpriteData = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)manTiles, 3);
	Sprite* manSprite = new Sprite(manSpriteData);

	dmaCopy(manPal, SPRITE_PALETTE_SUB, 512);

	int lolcounter = 0;
	while(1) {
		manSprite->draw();

		oamUpdate(&oamSub);
		swiWaitForVBlank();

		lolcounter++;
		if (lolcounter >= 10) {
			manSprite->nextFrame();
			lolcounter = 0;
		}
	}

	return 0;
}
