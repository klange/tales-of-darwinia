#include "playerentity.h"

void PlayerEntity::Update(InputManager* inputManager)
{
	touchPosition* touchXY = inputManager->moveToPosition(getPosition());

	/* Touchscreen position */
	Vector3<u16> touchPosition;

	// This section below is for touch screen sprite
	if (touchXY->px != NO_POSITION_FOUND && touchXY->py != NO_POSITION_FOUND) {
		touchPosition.setX(touchXY->px);
		touchPosition.setY(touchXY->py);
		setPosition(touchPosition);
	}

	delete touchXY;
}
