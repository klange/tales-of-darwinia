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

// WOW IT CONVERTS TO HEADER FILES COOL
#include "logo.h"
#include "sprite.h"

volatile int frame = 0;

void Vblank() {
	frame++;
	scanKeys();
	oamUpdate(&oamSub);
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

	/* Iniitate the sprite engine */
	oamInit(&oamSub, SpriteMapping_1D_32, false);
	SPRITE_PALETTE_SUB[1] = RGB15(31, 0, 0);

	/* Decompress and show the logo */
	int bg3 = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	decompress(logoBitmap, BG_GFX_SUB, LZ77Vram);

	/* Set up the console */
	PrintConsole topScreen;
	int bg1 = bgInit(1, BgType_Text4bpp, BgSize_T_256x256, 0, 0);
	consoleInit(&topScreen, 1, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

	/* Set the vertical blank event */
	irqSet(IRQ_VBLANK, Vblank);

	/* Iniitate the sprite engine */
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	/* Allocate memory for the sprite graphics */
	u16* gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);

	/* Sprite color */
	dmaFillHalfWords((1<<8)|1, gfx, 32*32);

	Sprite boxOfDoom;
	Position offset;
	offset.x = 8;
	offset.y = 8;
	boxOfDoom.anchorOffset = offset;
	boxOfDoom.gfx_buffer = gfx;

	Position targetPos;
	targetPos.x = 32;
	targetPos.y = 32;

	boxOfDoom.pos.x = 16;
	boxOfDoom.pos.y = 16;

	/* Hide title */
	bool bg3_hidden = false;

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

			targetPos.x = touchXY.px;
			targetPos.y = touchXY.py;
		}

		boxOfDoom.pos.x = (targetPos.x - boxOfDoom.pos.x)/10.0 + boxOfDoom.pos.x;
		boxOfDoom.pos.y = (targetPos.y - boxOfDoom.pos.y)/10.0 + boxOfDoom.pos.y;

		drawSprite(&boxOfDoom);

		iprintf("\033[23;0H%d  %d,%d", frame, touchXY.px, touchXY.py);

		bgUpdate();
	}

	return 0;
}
