#include "enemyentity.h"
#include "inputmanager.h"
#include "playerentity.h"
#include "audiomanager.h"

#include <stdio.h>

void EnemyEntity::Update()
{
	speed = 1.0;
	LivingEntity::Update();
	Vector3<s16> touchPos;
	if(gInputManager.getCurrentTouchPosition(touchPos))
	{
		//printf("touchPos = %d,%d\n", touchPos.x(), touchPos.y());
		BoundingBox<s16> bb;
		getBoundingBox(bb);
		//printf("topLeft = %d,%d\n", bb.mTopLeft.x(), bb.mTopLeft.y());
		//printf("bottomRight = %d,%d\n", bb.mBottomRight.x(), bb.mBottomRight.y());
		if(bb.PointInside(touchPos))
		{
			Vector3<s16> toPlayer = gpPlayerEntity->position - this->position;
			if(toPlayer.magnitude() < 32)
			{
				printf("Ouch!");
				audioManager.playSound(SFX_OUCH);
			}
		}
	}

	this->setTargetPosition(gpPlayerEntity->position);
}
