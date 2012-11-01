/* vim: ts=4 sw=4 noexpandtab
 *
 * Map engine code
 */

#include <nds.h>
#include "maps.h"

MapEngine::MapEngine(
		const int palette_len,
		const u16* palette,
		const int tiles_len,
		const u8** tiles,
		const int map_height,
		const int map_width,
		const u16* map
	) : palette_len(palette_len),
		palette(palette),
		tiles_len(tiles_len),
		tiles(tiles),
		map_height(map_height),
		map_width(map_width),
		map(map) {
	/* Init the tile and scroll position,
	 * Top-Left corner is 0,0 for screen and tiles
	 *
	 * Scroll position is the offset for displaying
	 * the 64x64 map frame on the display
	 */
}

int MapEngine::dumpPaletteToVRAM(u16* palette_memory) {
	// Load the palette
//	for (int i = 0; i < palette_len; i++) {
//		*(palette_memory + i) = palette[i];
//	}
	dmaCopy(palette, palette_memory, (sizeof(palette) * palette_len));
	return 0;
}

int MapEngine::dumpTilesToVRAM(u8* tile_memory) {
	// Since we got an pointer to an array of pointers that
	// points to each 8x8 array of tiles data, copy each tile
	// data into the right spot one at a time.
	for (int i = 0; i < tiles_len; i++) {
		// Pointer to an array
		// array of pointers to an array of tile data (64)
		u8* ptrToTile = (u8*)tiles[i];

//		for (int j = 0; j < 64; j++) {
//			*(tile_memory + (64*i) + j) = ptrToTile[j];
//		}
		dmaCopy(ptrToTile, (tile_memory + (64*i)), 32);
	}
	return 0;
}

int MapEngine::dumpMapToVRAM(u16* map_memory) {
	// Load the map for now we assume 64x64
//	for (int i = 0; i < (map_width * map_height); i++) {
//		*(map_memory + i) = map[i];
//	}
	dmaCopy(map, map_memory, (sizeof(map) * map_width * map_height));
	return 0;
}

int MapEngine::getTileX(int screen_pixel_x) {
	return 0;
}

int MapEngine::getTileY(int screen_pixel_y) {
	return 0;
}

/*
int maps_main(void) {

	//get the address of the tile and map blocks
	u8* tileMemory = (u8*)BG_TILE_RAM(1);
	u16* mapMemory = (u16*)BG_MAP_RAM(0);

	//tell the DS where we are putting everything and set 256 color mode and that we are using a 64 by 64 tile map.
	REG_BG0CNT = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

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
}*/
