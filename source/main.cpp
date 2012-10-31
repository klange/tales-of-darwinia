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

#include "logo.h"
#include "vector3.h"

volatile int frame = 0;

void Vblank() {
	frame++;
	scanKeys();
}

int main(void) {
	/* Touchscreen position */
	touchPosition touchXY;

	/* Force the main engine to top screen */
	lcdMainOnTop();

	/* Set the mode for 2 text layers and two extended background layers */
	videoSetMode(MODE_5_2D | DISPLAY_BG1_ACTIVE | DISPLAY_BG3_ACTIVE);
	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankB(VRAM_B_MAIN_BG);

	/* Set the mode for sprite display */
	videoSetModeSub(MODE_5_2D | DISPLAY_SPR_ACTIVE);
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	/* Set the default backgorund color */
	setBackdropColor(0xF);

	/* Decompress and show the logo */
	int bg3 = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	decompress(logoBitmap, BG_GFX_SUB, LZ77Vram);

	/* Set up the console */
	PrintConsole topScreen;
	int bg1 = bgInit(1, BgType_Text4bpp, BgSize_T_256x256, 0, 0);
	consoleInit(&topScreen, 1, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

	/* Set the vertical blank event */
	irqSet(IRQ_VBLANK, Vblank);

	/* Hide title */
	bool bg3_hidden = false;

	Vector3<u16>* derp = new Vector3<u16>(1, 2, 3);

	while(1) {
		swiWaitForVBlank();

		SPRITE_PALETTE_SUB[1] = RGB15(0, frame % 32, 0);

		if (keysUp() & KEY_START) bg3_hidden = !bg3_hidden;
		if (bg3_hidden) {
			bgHide(bg3);
			bgShow(bg1);
		} else {
			bgHide(bg1);
			bgShow(bg3);
		}

		// This section below is for touch screen sprite
		if (keysHeld() & KEY_TOUCH) {
			touchRead(&touchXY);
		}

		// WHY WON'T YOU WORK WTF :(
		derp->setX(touchXY.px);
		derp->setY(touchXY.py);

		// Y U NO WORK
		u16 asdf[2];
		asdf[0] = touchXY.px;
		asdf[1] = touchXY.py;

		iprintf("\033[23;0H%d  %d,%d", frame, asdf[0], asdf[1]);

		bgUpdate();
	}

	return 0;
}
