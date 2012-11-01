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
#include "event.h"
#include "eventdispatcher.h"

#include "dispatch.h"

// Sound!
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

volatile int frame = 0;



void Vblank() {
	frame++;
}

void hahaOhMan(void* eventArgs) {
	//boxSprite.nextFrame();
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

	/* Set up the console */
	PrintConsole topScreen;
	bgInit(1, BgType_Text4bpp, BgSize_T_256x256, 0, 0);
	consoleInit(&topScreen, 1, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	Vector3<u16> touchPosition;

	/* Set the vertical blank event */
	irqSet(IRQ_VBLANK, Vblank);

	/* Hide title */
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoad(MOD_TECHNO_MOZART);
	mmStart(MOD_TECHNO_MOZART, MM_PLAY_LOOP);

	Event* derpyEvent;
	derpyEvent = (Event*)malloc(sizeof(Event));
	derpyEvent->eventCallback = hahaOhMan;
	derpyEvent->type = BUTTON_PRESS;
	derpyEvent->enabled = true;

	SpriteData* manSpriteData = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)manTiles, 3);

	Sprite* manSprite = new Sprite(manSpriteData);
	dmaCopy(manPal, SPRITE_PALETTE_SUB, 512);

	while(1) {
		scanKeys();
		globalDispatcher->addEvent(derpyEvent);

		if (keysHeld() & KEY_TOUCH) {
			touchRead(&touchXY);
		}

		touchPosition.setX(touchXY.px);
		touchPosition.setY(touchXY.py);

		manSprite->setPosition(touchPosition);
		
		manSprite->doRender(NULL);

		globalDispatcher->dispatchEvents();
		oamUpdate(&oamSub);
		swiWaitForVBlank();

		manSprite->nextFrame();
	}

	return 0;
}
