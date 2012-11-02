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

#include "audiomanager.h"

#include "gamelevel.h"
#include "gamelevel_data.h"

void Vblank(void) {
	
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
	bgInitSub(0, BgType_Text8bpp, BgSize_T_512x512, 0, 1);
//	REG_BG0CNT = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	/* Vertical offset for scrolling the map in pixels */
	REG_BG0VOFS = 64;

	/* Decompress and show the logo */
	if(!USE_TOP_SCREEN_FOR_CONSOLE)
	{
		bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
		decompress(logoBitmap, BG_GFX, LZ77Vram);
	}

	/* Make the darwin sprite */
	SpriteData* gfx = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)darwinTiles, 3);

	/* Make a man enemy sprite */
	SpriteData* gfx2 = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)manTiles, 3);
	dmaCopy(manPal, SPRITE_PALETTE_SUB, 512);

	PlayerEntity* playerEntity = new PlayerEntity(gfx);
	playerEntity->Init();
	playerEntity->size = Vector3<s16>(32,32,0);
	playerEntity->setPosition(Vector3<s16>(64,90,1));
	playerEntity->setTargetPosition(Vector3<s16>(0,0,0));

	EnemyEntity* enemyEntity = new EnemyEntity(gfx2);
	enemyEntity->Init();
	enemyEntity->size = Vector3<s16>(32,32,0);
	enemyEntity->setPosition(Vector3<s16>(192,90,0));
	enemyEntity->setTargetPosition(Vector3<s16>(0,0,0));

	audioManager.initialize();

	levelLoader.load(GAME_LEVELS[0]);

	touchPosition touchXY;

	int lolcounter = 0;
	while(1) {
		scanKeys();
		if (keysHeld() & KEY_TOUCH) {
			touchRead(&touchXY);
		}

		gInputManager.Update();
		gEntityManager.Update();
		gEntityManager.Render();

		lolcounter++;
		if (lolcounter >= 10) {
			gEntityManager.NextFrame();
			lolcounter = 0;

		}
		enemyEntity->setTargetPosition(playerEntity->position);

		oamUpdate(&oamSub);
		bgUpdate();

		swiWaitForVBlank();
	}

	return 0;
}
