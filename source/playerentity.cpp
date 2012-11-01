#include "playerentity.h"

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
	}
}
