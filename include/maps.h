#ifndef MAPS_H_
#define MAPS_H_

#include <nds.h>
#include "map_type.h"

/**
 * A class that deals with the loading and unloading of viewable map
 * area to the hardware
 */
class MapEngine {
	private:
		/* The palette for all loaded tiles */
		const palette_t* palette;

		/* The list of all tiles used */
		const tile_list_t* tiles;

		/* The actual map data itself */
		const map_t* map;

		/* Current "display" scroll offset in pixels */
		int scroll_x, scroll_y;

		/* Map offset */
		int map_x, map_y;

	public:
		MapEngine(
			const palette_t* a_palette,
			const tile_list_t* a_tiles,
			const map_t* a_map
		);

		void dumpPaletteToVRAM(u16* palette_memory);
		void dumpTilesToVRAM(u8* tile_memory);
		void dumpMapToVRAM(u16* map_memory);

		int getTileX(int screen_pixel_x);
		int getTileY(int screen_pixel_y);

		void scrollMapAbsolute(int bg, int pixel_x, int pixel_y);
};

#endif
