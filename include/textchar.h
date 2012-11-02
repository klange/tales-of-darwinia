#ifndef TEXT_CHAR_H_
#define TEXT_CHAR_H_

#include "spritedata.h"
#include "livingentity.h"

class TextChar : public LivingEntity
{
public:
 TextChar(SpriteData* gfx) : LivingEntity(gfx) {}
	virtual void Update();
};

#endif // TEXT_CHAR_H_
