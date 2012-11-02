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

#include "darwin.h"
#include "man.h"
#include "logo.h"
#include "sprite.h"
#include "entitymanager.h"
#include "event.h"
#include "eventdispatcher.h"
#include "inputmanager.h"
#include "playerentity.h"
#include "enemyentity.h"

#include "dispatch.h"

/* Maps */
#include "maps.h"
#include "map_data.h"

#include "audiomanager.h"

#include "sprite.h"
#include "spritedata.h"

void Vblank(void) {
	
}

void init(void) {
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

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	/* Set the vertical blank event */
	irqSet(IRQ_VBLANK, Vblank);
}

int main(void) {
	/* Put any generic engine/game init code in the init () */
	init();

	/* Load data from map_data.h into the map engine */
	MapEngine mapEngine = MapEngine(
		tile_palette_len,
		tile_palette,
		tile_list_len,
		tile_list,
		map_height,
		map_width,
		map
	);
	mapEngine.dumpTilesToVRAM();

	/* Decompress and show the logo */
	int bg3 = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	decompress(logoBitmap, BG_GFX_SUB, LZ77Vram);

	/* Set up the console */
	PrintConsole topScreen;
	int bg1 = bgInit(1, BgType_Text4bpp, BgSize_T_256x256, 0, 0);
	consoleInit(&topScreen, 1, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

	SpriteData* gfx = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)darwinTiles, 3);
	SpriteData* gfx2 = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)manTiles, 3);

	dmaCopy(darwinPal, SPRITE_PALETTE_SUB, 512);

	gEntityManager.Init();

	PlayerEntity* playerEntity = new PlayerEntity(gfx);
	playerEntity->Init();
	playerEntity->setPosition(Vector3<u16>(64,90,1));

	EnemyEntity* enemyEntity = new EnemyEntity(gfx2);
	enemyEntity->Init();
	enemyEntity->setPosition(Vector3<u16>(192,90,0));

	/* Hide title */
	bool bg3_hidden = false;
	audioManager.initialize();
	audioManager.playMusic(MOD_TECHNO_MOZART);

	while(1) {

		if (keysUp() & KEY_START) bg3_hidden = !bg3_hidden;
		if (bg3_hidden) {
			bgHide(bg3);
			bgShow(bg1);
		} else {
			bgHide(bg1);
			bgShow(bg3);
		}

		gEntityManager.Update();
		gEntityManager.Render();

		oamUpdate(&oamSub);
		bgUpdate();

		swiWaitForVBlank();
	}

	return 0;
}
