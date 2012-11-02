#include "itementity.h"
#include "audiomanager.h"
#include "playerentity.h"

#define SFX_CONSUME_ITEM SFX_CHOMP


char* NAMES_BY_ITEM_TYPE[] = {
	NULL, // ITEM_UNKNOWN
	"Peanut butter",
	"Chocolate",
	"Drumstick",
	NULL,
};


ItemEntity::ItemEntity(SpriteData* inSpriteData, LivingStats* stats, ItemType type) : Sprite(inSpriteData)
{
	this->type = type;
	this->mStats = stats->clone();
}

ItemEntity::~ItemEntity()
{
	delete mStats;
}

LivingStats* ItemEntity::Consume()
{
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
		mStats->Print(NAMES_BY_ITEM_TYPE[type]);
		gpPlayerEntity->Collect(this);
	}

	Sprite::Update();
}
