#ifndef ITEM_ENTITY_H_
#define ITEM_ENTITY_H_

#include "sprite.h"
#include "livingstats.h"


/**
 * An item that can be picked up.
 *
 * Currently items are merely consumables that change the users's stats.  If
 * we want to make an item that is keepable (e.g. weapon, tradeable buf item)
 * we should split that out.
 */
class ItemEntity : public Sprite
{
public:
	ItemEntity(SpriteData* inSpriteData, LivingStats* stats);

	LivingStats* Consume();

private:
	LivingStats* mStats;
};

#endif // ITEM_ENTITY_H_
