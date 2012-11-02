#include "playerentity.h"
#include "audiomanager.h"

#define SFX_PLAYER_MOVE SFX_DOG_BARK

void PlayerEntity::Update(InputManager* inputManager)
{
	touchPosition* touchXY = inputManager->moveToPosition(getPosition(), 2.0);

	/* Touchscreen position */
	Vector3<s16> touchPosition;

	// This section below is for touch screen sprite
	if (touchXY != NULL){
		touchPosition.setX(touchXY->px);
		touchPosition.setY(touchXY->py);
		setPosition(touchPosition);

		audioManager.playSound(SFX_PLAYER_MOVE);
	}

	delete touchXY;
}
