#include "itementity.h"
#include "audiomanager.h"

#define SFX_CONSUME_ITEM SFX_R2D2

ItemEntity::ItemEntity(SpriteData* inSpriteData, LivingStats* stats) : Sprite(inSpriteData)
{
	this->mStats = stats;
}

LivingStats* ItemEntity::Consume()
{
	audioManager.playSound(SFX_CONSUME_ITEM);
	return this->mStats;
}
