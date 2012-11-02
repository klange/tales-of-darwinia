#include "playerentity.h"
#include "audiomanager.h"
#include "inputmanager.h"

#define SFX_PLAYER_MOVE SFX_DOG_BARK

#define speed 3
void PlayerEntity::Update()
{
	LivingEntity::Update();

	if (keysHeld() & KEY_TOUCH) {
		touchPosition curTouchPosition;
		touchRead(&curTouchPosition);
		setTargetPosition(Vector3<s16>(curTouchPosition.px, curTouchPosition.py, 1));
	}

	if (directionVector.x() < 0) {
		spriteOffset = 1;
		vflip = true;
	} else if (directionVector.x() >= 0) {
		spriteOffset = 1;
		vflip = false;
	}
}
