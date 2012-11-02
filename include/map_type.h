#ifndef MAP_TYPE_H_
#define MAP_TYPE_H_

#include <nds.h>

/*
 * Tile defines are hardcoded to the nds engine limits
 *
 * Palette defines are capped at 256 entries
 *
 * Map defines are hardcoded cos we'll support dynamic map
 * size via compiling in the maps with adjusted defines
 */
#define TILE_WIDTH 8
#define TILE_HEIGHT 8
#define TILE_SIZE (TILE_WIDTH * TILE_HEIGHT)

// TODO: should not need these
#define TILE_ENTRIES 96
#define PALETTE_ENTRIES 16

#define MAP_WIDTH 64
#define MAP_HEIGHT 64
#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT)

// Screen dim
#define SCREEN_HEIGHT 192
#define SCREEN_WIDTH 256

// World boundaries
#define MAP_SCREEN_HEIGHT ((MAP_HEIGHT - (SCREEN_HEIGHT / TILE_HEIGHT)) * TILE_HEIGHT)
#define MAP_SCREEN_WIDTH ((MAP_WIDTH - (SCREEN_WIDTH / TILE_WIDTH)) * TILE_WIDTH)

/* Palette typedef */
typedef u16 palette_t[PALETTE_ENTRIES];

/* Tiles typedef */
typedef u8 tile_t[TILE_SIZE];
typedef tile_t * tile_list_t[TILE_ENTRIES];

/* Maps typedef */
typedef u16 map_t[MAP_SIZE];

#endif
