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

void init(void) {
	/* Force the main engine to top screen */
	lcdMainOnTop();

	/* Set the mode for 2 text layers and two extended background layers */
	videoSetMode(MODE_5_2D | DISPLAY_BG2_ACTIVE);
	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankB(VRAM_B_MAIN_BG);

	/* Set the mode for sprite display */
	videoSetModeSub(MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_SPR_ACTIVE);
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	/* Set the default backgorund color */
	setBackdropColor(0xF);

	/* Set the vertical blank event */
	irqSet(IRQ_VBLANK, Vblank);
}

int main(void) {
	/* Put any generic engine/game init code in the init () */
	init();

	/* Load data from map_data.h into the map engine */
	MapEngine mapEngine = MapEngine(
		&tile_palette,
		&tile_set,
		&map
	);

	/* Tile engine is going to claim BG0 */
	int tile = bgInitSub(0, BgType_Text8bpp, BgSize_T_512x512, 0, 1);
//	REG_BG0CNT = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	/* Load the relevant data into the VRAM */
	mapEngine.dumpPaletteToVRAM(&BG_PALETTE_SUB[0]);
	mapEngine.dumpTilesToVRAM((u8*)BG_TILE_RAM_SUB(1));
	mapEngine.dumpMapToVRAM((u16*)BG_MAP_RAM_SUB(0));

	/* Vertical offset for scrolling the map in pixels */
	REG_BG0VOFS = 64;

	/* Decompress and show the logo */
	int logo = bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	decompress(logoBitmap, BG_GFX, LZ77Vram);

	/* Set up the console */
//	PrintConsole topScreen;
//	int bg1 = bgInit(1, BgType_Text4bpp, BgSize_T_256x256, 0, 0);
//	consoleInit(&topScreen, 1, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

	/* Setup the sprites */
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	u16* gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
	for (int i = 0; i < 16 * 16 / 2; i++) {
		gfx[i] = 1 | (1 << 8);
	}

	u16* gfx2 = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
	for (int i = 0; i < 16 * 16 / 2; i++) {
		gfx2[i] = 1 | (1 << 8);
	}

	SPRITE_PALETTE_SUB[1] = RGB15(31, 0, 0);

	gEntityManager.Init();

	PlayerEntity* playerEntity = new PlayerEntity(gfx);
	playerEntity->Init();
	playerEntity->setPosition(Vector3<u16>(64,90,1));

	EnemyEntity* enemyEntity = new EnemyEntity(gfx2);
	enemyEntity->Init();
	enemyEntity->setPosition(Vector3<u16>(192,90,0));

	audioManager.initialize();
	audioManager.playMusic(MOD_TECHNO_MOZART);

	Event* derpyEvent;
	derpyEvent = (Event*)malloc(sizeof(Event));
	derpyEvent->eventCallback = hahaOhMan;
	derpyEvent->type = BUTTON_HOLD;
	derpyEvent->enabled = true;

	Event* drawEvent;
	drawEvent = (Event*)malloc(sizeof(Event));
	//drawEvent->eventCallback = playerEntity->doRender;
	drawEvent->type = BUTTON_HOLD;
	drawEvent->enabled = true;

	while(1) {
		swiWaitForVBlank();
		globalDispatcher->addEvent(derpyEvent);
		//globalDispatcher->addEvent(drawEvent);

		SPRITE_PALETTE_SUB[1] = RGB15(0, frame % 32, 0);

		gEntityManager.Update();
		gEntityManager.Render();

		bgUpdate();
	}

	return 0;
}
