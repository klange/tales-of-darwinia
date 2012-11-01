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

#include "map_data.h"

int main(void) {
	//set video mode and map vram to the background
	videoSetMode(MODE_0_2D | DISPLAY_BG0_ACTIVE);
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);

	//get the address of the tile and map blocks
	u8* tileMemory = (u8*)BG_TILE_RAM(1);
	u16* mapMemory = (u16*)BG_MAP_RAM(0);

	//tell the DS where we are putting everything and set 256 color mode and that we are using a 64 by 64 tile map.
	REG_BG0CNT = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	// Load the palette
	for (int i = 0; i < tile_palette_len; i++) {
		BG_PALETTE[i+1] = tile_palette[i];
	}

	// Copy each tile block into tile memory
	for (int i = 0; i < tile_list_len; i++) {
		swiCopy(tile_list[i], tileMemory + (0 * 64), 32);
	}

	// Copy the map into map memory
	swiCopy(map, mapMemory, (map_height * map_width)); // Half word = 16bit

	int scrollY = 64;
	while(1)
		REG_BG0VOFS = scrollY;
		swiWaitForVBlank();

	return 0;
}
