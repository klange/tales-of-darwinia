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

#include "logo.h"
#include "sprite.h"
#include "event.h"
#include "eventdispatcher.h"

#include "dispatch.h"

/* Maps */
#include "maps.h"

// Sound!
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

volatile int frame = 0;

void Vblank() {
	frame++;
	scanKeys();
	oamUpdate(&oamSub);

	globalDispatcher->dispatchEvents();
}

void hahaOhMan(void* eventArgs) {
	iprintf("\033[23;0H%d  ", frame);
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
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	u16* gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);	

	for (int i = 0; i < 16 * 16 / 2; i++) {
		gfx[i] = 1 | (1 << 8);
	}

	SPRITE_PALETTE_SUB[1] = RGB15(31, 0, 0);

	Sprite boxSprite = Sprite(gfx);
	Vector3<u16> touchPosition;

	/* Set the vertical blank event */
	irqSet(IRQ_VBLANK, Vblank);

	/* Hide title */
	bool bg3_hidden = false;
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoad(MOD_TECHNO_MOZART);
	mmStart(MOD_TECHNO_MOZART, MM_PLAY_LOOP);

	Event* derpyEvent;
	derpyEvent = (Event*)malloc(sizeof(Event));
	derpyEvent->eventCallback = hahaOhMan;
	derpyEvent->type = BUTTON_HOLD;
	derpyEvent->enabled = true;

	Event* drawEvent;
	drawEvent = (Event*)malloc(sizeof(Event));
	//drawEvent->eventCallback = boxSprite.doRender;
	drawEvent->type = BUTTON_HOLD;
	drawEvent->enabled = true;

	while(1) {
		swiWaitForVBlank();
		globalDispatcher->addEvent(derpyEvent);
		//globalDispatcher->addEvent(drawEvent);

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
		touchPosition.setX(touchXY.px);
		touchPosition.setY(touchXY.py);
		boxSprite.setPosition(touchPosition);
		boxSprite.doRender(NULL);
		bgUpdate();
	}

	return 0;
}
