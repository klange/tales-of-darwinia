/* vim: ts=4 sw=4 noexpandtab
 * Tales of Darwinia
 *
 * A Game by Yelp Engineers
 *
 * Henri Bai
 * Paul Berens
 * Patrick Tiet
 * Kevin Lange
 * MAYBE YOU!
 *
 */

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int frame = 0;

void Vblank() {
	frame++;
}

int main(void) {
	touchPosition touchXY;
	PrintConsole top_screen;

	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	/* this shit is confusing */
	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	/* that shit was confusing */

	oamInit(&oamSub, SpriteMapping_1D_32, false);

	u16* gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);

	for (int i = 0; i < 16 * 16 / 2; i++) {
		gfx[i] = 1 | (1 << 8);
	}

	SPRITE_PALETTE_SUB[1] = RGB15(31, 0, 0);

	consoleInit(&top_screen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
	irqSet(IRQ_VBLANK, Vblank);

	iprintf("Tales of Darwinia: TRASH EATAR\n");

	while(1) {
		swiWaitForVBlank();
		touchRead(&touchXY);

		iprintf("\033[23;0H%d  %d,%d        ", frame, touchXY.px, touchXY.py);

		oamSet(
			&oamSub,
			0, // oam index
			touchXY.px, // x location of sprite
			touchXY.py, // y location of sprite
			0, // z-index
			0, // palette index (i have no clue wtf this does)
			SpriteSize_16x16,
			SpriteColorFormat_256Color,
			gfx, // pointer to the actualy graphic
			-1, // rotation
			false, // double the size when rotating?
			false, // hide?
			false, // vflip
			false, // hflip
			false //apply mosaic, what does this do?
		);

		oamUpdate(&oamSub);


	
	}

	return 0;
}
