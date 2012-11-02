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
 * Matt G
 * Tom R
 * MAYBE YOU!
 *
 */

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "man.h"
#include "darwin.h"
#include "inconsolata.h"
#include "logo.h"
#include "sprite.h"
#include "entitymanager.h"
#include "event.h"
#include "eventdispatcher.h"
#include "inputmanager.h"
#include "playerentity.h"
#include "enemyentity.h"
#include "text.h"
#include "textchar.h"

/* Maps */
#include "maps.h"
#include "map_data.h"

#include "audiomanager.h"

#include "gamelevel.h"
#include "gamelevel_data.h"

void Vblank(void) {

}

SpriteData* gSpriteData[16];
TextChar* gTextChars[16];

void blitText(const char* text, int len) {
  if (len > 16) len = 16;
  for (int i = 0; i < len; ++i) {
    gTextChars[i]->setFrame(text[i]);
  }
}
// HEY PEEPS - set this to 1 for PRINTF DEBUGGING GOODNESS!
#define USE_TOP_SCREEN_FOR_CONSOLE 1
PrintConsole* gpTopScreen = NULL;

void init(void) {
	/* Force the main engine to top screen */
	lcdMainOnTop();

	if(USE_TOP_SCREEN_FOR_CONSOLE)
	{
		gpTopScreen = new PrintConsole();

		videoSetMode(MODE_0_2D);
		//videoSetModeSub(MODE_0_2D);

		vramSetBankA(VRAM_A_MAIN_BG);
		//vramSetBankC(VRAM_C_SUB_BG);

		consoleInit(gpTopScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
		consoleSelect(gpTopScreen);
	}
	else
	{
		/* Set the mode for 2 text layers and two extended background layers */
		videoSetMode(MODE_5_2D | DISPLAY_BG2_ACTIVE);
		vramSetBankA(VRAM_A_MAIN_BG);
		vramSetBankB(VRAM_B_MAIN_BG);
	}

	/* Set the mode for sprite display */
	videoSetModeSub(MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_SPR_ACTIVE);
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	/* Initialize the entity manager */
	gEntityManager.Init();

	/* Initialize the event dispatcher */
	gEventDispatcher.Init();

	/* Set the default backgorund color */
	setBackdropColor(0xF);
	setBackdropColorSub(0xE);

	//oamInit(&oamMain, SpriteMapping_1D_128, false);
	/* Initiate the sprite engine */
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	/* Set the vertical blank event */
	irqSet(IRQ_VBLANK, Vblank);
}

int main(void) {
	/* Put any generic engine/game init code in the init () */
	init();

	/* Tile engine is going to claim BG0 */
	int tile = bgInitSub(0, BgType_Text8bpp, BgSize_T_512x512, 0, 1);
	REG_BG0CNT_SUB = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	/* Decompress and show the logo */
	//bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	//decompress(logoBitmap, BG_GFX, LZ77Vram);

	/*
	if(!USE_TOP_SCREEN_FOR_CONSOLE)
	{
		bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
		decompress(logoBitmap, BG_GFX, LZ77Vram);
	}
	*/

	audioManager.initialize();

	MapEngine mapEngine = levelLoader.load(GAME_LEVELS[0]);

	// Set up the text display

	for (int i = 0; i < 16; ++i) {
          gSpriteData[i] = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)inconsolataTiles, 255);
    	  gTextChars[i] = new TextChar(gSpriteData[i]);
	  gTextChars[i]->isAnimated = false;
	  gTextChars[i]->Init();
	  gTextChars[i]->size = Vector3<s16>(1,1,0);
	  gTextChars[i]->setPosition(Vector3<s16>(40+(i*12),20,1));
	  gTextChars[i]->setFrame(0x9);
	}

	blitText("BARK0123456789", 14);

	touchPosition touchXY;

	int lolcounter = 0;
	while(1) {
		scanKeys();
		if (keysHeld() & KEY_TOUCH) {
			touchRead(&touchXY);
		}

		int rel_x = 0;
		int rel_y = 0;
		if (keysHeld() & KEY_LEFT) {
			rel_x = -1;
		}
		if (keysHeld() & KEY_RIGHT) {
			rel_x = 1;
		}
		if (keysHeld() & KEY_UP) {
			rel_y = -1;
		}
		if (keysHeld() & KEY_DOWN) {
			rel_y = 1;
		}
		mapEngine.scrollMapRelative(tile, rel_x, rel_y);

		gInputManager.Update();
		gEntityManager.Update();
		gEntityManager.Render();

		lolcounter++;
		if (lolcounter >= 10) {
			gEntityManager.NextFrame();
			lolcounter = 0;
		}

		oamUpdate(&oamSub);
		bgUpdate();

		swiWaitForVBlank();
	}

	return 0;
}
