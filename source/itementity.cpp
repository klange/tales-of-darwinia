#include "itementity.h"
#include "audiomanager.h"

#define SFX_CONSUME_ITEM SFX_R2D2

LivingStats* ItemEntity::Consume()
{
	audioManager.playSound(SFX_CONSUME_ITEM);
	return this->mStats;
}
