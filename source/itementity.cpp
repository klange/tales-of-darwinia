#include "itementity.h"
#include "audiomanager.h"
#include "playerentity.h"

#define SFX_CONSUME_ITEM SFX_R2D2

ItemEntity::ItemEntity(SpriteData* inSpriteData, LivingStats* stats) : Sprite(inSpriteData)
{
	this->mStats = stats;
}

LivingStats* ItemEntity::Consume()
{
	audioManager.playSound(SFX_CONSUME_ITEM);
	shouldBeRemoved = true;
	hidden = true;
	return this->mStats;
}

void ItemEntity::Update()
{
	if (shouldBeRemoved)
		return;

	if (IsTouchedByNearbyPlayer())
	{
		// TODO: play munch sound
		mStats->Print("Munch");
		gpPlayerEntity->Collect(this);
	}

	Sprite::Update();
}
