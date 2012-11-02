#ifndef MAPS_H_
#define MAPS_H_

#include <nds.h>
#include "map_type.h"

#define WALK   (0x00)
#define NOWALK (0x01)
#define IDX_MASK (0x03FF) // bit 15-12 (palette), bit 11-10 (flip) bit 9-0 (idx)

// forward declarations
class MapEngine;

// Yep! This is ugly.
extern int gMapTileIndex;
extern MapEngine* gpMapEngine;

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

		/* The actual list of nowalk tile idx */
		const nowalk_t* nowalk_idx;

		/* Current "display" scroll offset in pixels */
		int scroll_x, scroll_y;

		/* Map offset */
		int map_x, map_y;

		/* Pointer to the memory area to update in VRAM when we have
		 * new data to update with
		 */
		u16* palette_memory;
		u8* tile_memory;
		u16* map_memory;

		/* Pointer to the newly generated collision map generated from
		 * a map
		 */
		u8* collision_memory;

		/* All of the data operation to load new data into VRAM */
		void dumpPaletteToVRAM(u16* palette_memory);
		void dumpTilesToVRAM(u8* tile_memory);
		void dumpMapToVRAM(u16* map_memory);

		/* Generate a collision map */
		void generateCollisionMap();

	public:
		MapEngine(
			const palette_t* a_palette,
			const tile_list_t* a_tiles,
			const map_t* a_map,
			const nowalk_t* a_nowalk
		);
		~MapEngine();

		void initVRAM(
			u16* a_palette_memory,
			u8* a_tile_memory,
			u16* a_map_memory
		);

		int getScrollX() { return scroll_x; }
		int getScrollY() { return scroll_y; }

		int getTileX(int screen_pixel_x);
		int getTileY(int screen_pixel_y);

		void scrollMapAbsolute(int bg, int abs_x, int abs_y);
		void scrollMapRelative(int bg, int rel_x, int rel_y);

		bool collisionAbsolute(int abs_x, int abs_y);
		bool collisionRelative(int rel_x, int rel_y);
};

#endif
