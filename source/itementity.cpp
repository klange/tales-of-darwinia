#include "itementity.h"
#include "audiomanager.h"
#include "inputmanager.h"
#include "playerentity.h"

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
}

/**
 * Helper that an entity's Update method can use to check if we are being touched
 *
 * TODO: move this to a GameEntity that both LivingEntity and ItemEntity inherit from.
 * Such a GameEntity would be a Sprite.
 */
bool ItemEntity::IsTouchedByNearbyPlayer()
{
	Vector3<s16> touchPos;
	if(gInputManager.getCurrentTouchPosition(touchPos))
	{
		BoundingBox<s16> bb;
		getBoundingBox(bb);
		if (bb.PointInside(touchPos))
		{
			Vector3<s16> toPlayer = gpPlayerEntity->position - this->position;
			if (toPlayer.magnitude() < 32)
			{
				return true;
			}
		}
	}
	return false;
}

