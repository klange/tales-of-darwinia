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
	scroll_x = scroll_y = 0;
	map_x = map_y = 0;
}

void MapEngine::initVRAM(
		u16* a_palette_memory,
		u8* a_tile_memory,
		u16* a_map_memory) {
	palette_memory = a_palette_memory;
	tile_memory = a_tile_memory;
	map_memory = a_map_memory;

	dumpPaletteToVRAM(palette_memory);
	dumpTilesToVRAM(tile_memory);
	dumpMapToVRAM(map_memory);
}

void MapEngine::dumpPaletteToVRAM(u16* palette_memory) {
	// Load the palette
	// dmaCopy copies in halfword (16bits), a palette entry is 16bit
	dmaCopy(palette, palette_memory, PALETTE_ENTRIES);
}

void MapEngine::dumpTilesToVRAM(u8* tile_memory) {
	for (int i = 0; i < TILE_ENTRIES; i++) {
		tile_t* ptrToTile = (*tiles)[i];

		// dmaCopy copies in halfword (16bits), a tile entry is 8bit
		dmaCopy(ptrToTile, (tile_memory + (TILE_SIZE * i)), TILE_SIZE);
	}
}

void MapEngine::dumpMapToVRAM(u16* map_memory) {
	// Load the map for now we assume 64x64
	// dmaCopy copies in halfword (16bits), a map is 16bit
	dmaCopy(map, map_memory, MAP_SIZE);
}

int MapEngine::getTileX(int screen_pixel_x) {
	return 0;
}

int MapEngine::getTileY(int screen_pixel_y) {
	return 0;
}

void MapEngine::scrollMapAbsolute(int bg, int pixel_x, int pixel_y) {
	/*
	 * Need to experiment with offsets limits, cos apparently it
	 * wraps in text mode, so need to limit/bound it...
	 */
	int offset_x = pixel_x - scroll_x;
	int offset_y = pixel_y - scroll_y;

	bgScroll(bg, offset_x, offset_y);

	scroll_x = pixel_x;
	scroll_y = pixel_y;
}

/*
	//tell the DS where we are putting everything and set 256 color mode and that we are using a 64 by 64 tile map.
	REG_BG0CNT = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);
}*/
