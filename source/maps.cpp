/* vim: ts=4 sw=4 noexpandtab
 *
 * Map engine code
 */

#include <nds.h>
#include "maps.h"

MapEngine::MapEngine(
		const palette_t* a_palette,
		const tile_list_t* a_tiles,
		const map_t* a_map
	) : palette(a_palette),
		tiles(a_tiles),
		map(a_map) {
	/* Init the tile and scroll position,
	 * Top-Left corner is 0,0 for screen and tiles
	 *
	 * Scroll position is the offset for displaying
	 * the 64x64 map frame on the display
	 */
}

int MapEngine::dumpPaletteToVRAM(u16* palette_memory) {
	// Load the palette
	// dmaCopy copies in halfword (16bits), a palette entry is 16bit
	dmaCopy(palette, palette_memory, PALETTE_ENTRIES);
	return 0;
}

int MapEngine::dumpTilesToVRAM(u8* tile_memory) {
	for (int i = 0; i < TILE_ENTRIES; i++) {
		tile_t* ptrToTile = (*tiles)[i];

		// dmaCopy copies in halfword (16bits), a tile entry is 8bit
		dmaCopy(ptrToTile, (tile_memory + (TILE_SIZE * i)), TILE_SIZE/2);
	}
	return 0;
}

int MapEngine::dumpMapToVRAM(u16* map_memory) {
	// Load the map for now we assume 64x64
	// dmaCopy copies in halfword (16bits), a map is 16bit
	dmaCopy(map, map_memory, MAP_SIZE);
	return 0;
}

int MapEngine::getTileX(int screen_pixel_x) {
	return 0;
}

int MapEngine::getTileY(int screen_pixel_y) {
	return 0;
}

/*
	//tell the DS where we are putting everything and set 256 color mode and that we are using a 64 by 64 tile map.
	REG_BG0CNT = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);
}*/
