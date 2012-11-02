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
	// dmaCopy copies in halfword (16bits)
	dmaCopy(
		palette,
		palette_memory,
		(sizeof((*palette)[0]) * PALETTE_ENTRIES)
	);
}

void MapEngine::dumpTilesToVRAM(u8* tile_memory) {
	for (int i = 0; i < TILE_ENTRIES; i++) {
		tile_t* ptrToTile = (*tiles)[i];

		// dmaCopy copies in halfword (16bits), a tile entry is 8bit
		dmaCopy(
			ptrToTile,
			(tile_memory + (TILE_SIZE * i)),
			(sizeof((*ptrToTile)[0]) * TILE_SIZE)
		);
	}
}

void MapEngine::dumpMapToVRAM(u16* map_memory) {
	// Load the map for now we assume 64x64
	// dmaCopy copies in halfword (16bits)
	dmaCopy(
		map,
		map_memory,
		(sizeof((*map)[0]) * MAP_SIZE)
	);
}

int MapEngine::getTileX(int screen_pixel_x) {
	return 0;
}

int MapEngine::getTileY(int screen_pixel_y) {
	return 0;
}

void MapEngine::scrollMapAbsolute(int bg, int abs_x, int abs_y) {
	int move_x = abs_x - scroll_x;
	int move_y = abs_y - scroll_y;

	// Check the boundaries of the new abs value
	if (abs_x < 0) {
		move_x = -scroll_x;
	}
	if (abs_x > MAP_SCREEN_WIDTH) {
		move_x = MAP_SCREEN_WIDTH - scroll_x;
	}
	if (abs_y < 0) {
		move_y = -scroll_y;
	}
	if (abs_y > MAP_SCREEN_HEIGHT) {
		move_y = MAP_SCREEN_HEIGHT - scroll_y;
	}

	// Now actually move the background
	bgScroll(bg, move_x, move_y);

	// Store the new scroll_value
	scroll_x += move_x;
	scroll_y += move_y;
}

void MapEngine::scrollMapRelative(int bg, int rel_x, int rel_y) {
	int move_x = rel_x;
	int move_y = rel_y;

	// Check the boundaries of the new_scroll and if it exceed limits
	// cap it
	if ((scroll_x + rel_x) < 0) {
		move_x = -scroll_x;
	}
	if ((scroll_x + rel_x) > MAP_SCREEN_WIDTH) {
		move_x = MAP_SCREEN_WIDTH - scroll_x;
	}
	if ((scroll_y + rel_y) < 0) {
		move_y = -scroll_y;
	}
	if ((scroll_y + rel_y) > MAP_SCREEN_HEIGHT) {
		move_y = MAP_SCREEN_HEIGHT - scroll_y;
	}

	// Now actually move the background
	bgScroll(bg, move_x, move_y);

	// Store the new scroll_value
	scroll_x += move_x;
	scroll_y += move_y;
}

/*
	//tell the DS where we are putting everything and set 256 color mode and that we are using a 64 by 64 tile map.
	REG_BG0CNT = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);
}*/
