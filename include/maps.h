#ifndef MAPS_H_
#define MAPS_H_

#include <nds.h>

/**
 * A class that deals with the loading and unloading of viewable map
 * area to the hardware
 */
class MapEngine {
	private:
		/* The palette for all loaded tiles */
		const int palette_len;
		const u16* palette;

		/* The list of all tiles used */
		const int tiles_len;
		const u8** tiles;

		/* The actual map data itself */
		const int map_height;
		const int map_width;
		const u16* map;

		/* Current "player" location in tiles unit */
		int x, y;

		/* Current "display" scroll offset in pixels */
		int scroll_x, scroll_y;

	public:
		MapEngine(
			const int palette_len,
			const u16* palette,
			const int tiles_len,
			const u8** tiles,
			const int map_height,
			const int map_width,
			const u16* map
		);

		int dumpPaletteToVRAM(u16* palette_memory);
		int dumpTilesToVRAM(u8* tile_memory);
		int dumpMapToVRAM(u16* map_memory);

		int getTileX(int screen_pixel_x);
		int getTileY(int screen_pixel_y);
};

#endif
