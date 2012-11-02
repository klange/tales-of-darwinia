#ifndef TEXT_CHAR_H_
#define TEXT_CHAR_H_

#include "spritedata.h"
#include "sprite.h"

class TextChar : public Sprite
{
public:
 TextChar(SpriteData* gfx) : Sprite(gfx) {}
	virtual void Update();
};

#endif // TEXT_CHAR_H_
