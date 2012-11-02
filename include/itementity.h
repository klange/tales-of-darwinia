#ifndef ITEM_ENTITY_H_
#define ITEM_ENTITY_H_

#include "sprite.h"
#include "livingstats.h"


// NOTE: if you add a new type here, make sure you add to the corresponding mappings in gamelevel.cpp
typedef enum _ItemType
{
	ITEM_UNKNOWN,
	ITEM_PEANUT_BUTTER,
	ITEM_CHOCOLATE,
	ITEM_DRUMSTICK,
	ITEM_KIBBLE,
	ITEM_BIT,
	ITEM_BONE,
	ITEM_CAT,
} ItemType;



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
	ItemEntity(SpriteData* inSpriteData, LivingStats* stats, ItemType type);
	~ItemEntity();

	virtual void Update(void);

	LivingStats* Consume();

private:
	ItemType type;
	LivingStats* mStats;
};

#endif // ITEM_ENTITY_H_
