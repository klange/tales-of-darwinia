#include "playerentity.h"
#include "audiomanager.h"

#define SFX_PLAYER_MOVE SFX_DOG_BARK

void PlayerEntity::Update()
{
	/* Touchscreen position */
	touchPosition touchXY;
	Vector3<u16> touchPosition;

	// This section below is for touch screen sprite
	if (keysHeld() & KEY_TOUCH) {
		touchRead(&touchXY);
		touchPosition.setX(touchXY.px);
		touchPosition.setY(touchXY.py);
		setPosition(touchPosition);

		audioManager.playSound(SFX_PLAYER_MOVE);
	}
}
