#include "playerentity.h"
#include "audiomanager.h"
#include "inputmanager.h"

#define SFX_PLAYER_MOVE SFX_DOG_BARK

void PlayerEntity::Update()
{
	Vector3<s16> destPosition;
	if (gInputManager.moveToPosition(getPosition(), 2.0, destPosition))
	{
		setPosition(destPosition);

		audioManager.playSound(SFX_PLAYER_MOVE);
	}
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
