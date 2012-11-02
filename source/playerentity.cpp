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

void PlayerEntity::Collect(ItemEntity* item)
{
	// in the future we might add this item to our inventory (e.g. weapon, tradable item).
	// for now items are consumables that just change our stats

	LivingStats* statsDelta = item->Consume();
	this->mStats.attack += statsDelta->attack;
	this->mStats.maxHealth += statsDelta->maxHealth;
	this->mStats.health += statsDelta->health;
	this->mStats.speed += statsDelta->speed;
	if (this->mStats.health > this->mStats.maxHealth)
	{
		this->mStats.health = this->mStats.maxHealth;
	}
}
