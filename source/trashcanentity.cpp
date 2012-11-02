#include "trashcanentity.h"
#include "playerentity.h"

#include <stdio.h>

void TrashCanEntity::Update()
{
	if(shouldBeRemoved)
		return;

	Vector3<s16> touchPos;
	if(gInputManager.getCurrentTouchPosition(touchPos))
	{
		BoundingBox<s16> bb;
		getBoundingBox(bb);
		if(bb.PointInside(touchPos))
		{
			Vector3<s16> toPlayer = gpPlayerEntity->position - this->position;
			if(toPlayer.magnitude() < 32)
			{
				LivingEntity::Damage(gpPlayerEntity->mStats->attack);
				printf("Trashcan Ouch %d!\n", mStats->health);
			}
		}
	}
}
