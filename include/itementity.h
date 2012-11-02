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

	virtual void Update(void);

	LivingStats* Consume();

	// TODO: move this to a GameEntity that both LivingEntity and ItemEntity inherit from.
	// it would be Sprite, Transformable too.
	bool IsTouchedByNearbyPlayer();

private:
	LivingStats* mStats;
};

#endif // ITEM_ENTITY_H_
