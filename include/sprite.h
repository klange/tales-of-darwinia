#ifndef SPRITE_H_
#define SPRITE_H_

#include <nds.h>

typedef struct {
	u16 x;
	u16 y;
} Position;

typedef struct {
	Position topLeft;
	Position bottomRight;
} BoundingBox;

typedef struct {
	Position pos;
	Position anchorOffset;
	BoundingBox boundingBox;
	u16* gfx_buffer;	
} Sprite;

void drawSprite(Sprite*);

#endif
