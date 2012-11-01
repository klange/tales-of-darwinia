#include "playerentity.h"
#include "audiomanager.h"

#define SFX_PLAYER_MOVE SFX_DOG_BARK

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
		audioManager.playSound(SFX_PLAYER_MOVE);
	}

	delete touchXY;
}
