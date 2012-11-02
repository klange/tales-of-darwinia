#include <stdio.h>
#include "playerentity.h"
#include "audiomanager.h"
#include "inputmanager.h"
#include "math.h"

#define SFX_PLAYER_MOVE SFX_DOG_BARK

PlayerEntity* gpPlayerEntity = NULL;

PlayerEntity::PlayerEntity(SpriteData* gfx) : LivingEntity(gfx)
{
	gpPlayerEntity = this;
	maxSpeed = 3;
	acceleration = 0.2;
}

PlayerEntity::~PlayerEntity()
{
	gpPlayerEntity = NULL;
}


void PlayerEntity::Update()
{
	if (keysHeld() & KEY_TOUCH) {
		touchPosition curTouchPosition;
		touchRead(&curTouchPosition);
		setTargetPosition(Vector3<s16>(curTouchPosition.px, curTouchPosition.py, 1));
		movementState = MOVING;
	}

	if (movementState == MOVING) {
		speed += acceleration;
	}

	if (movementState == STOPPED) {
		speed = 0;
	}
	if (speed < 0) {
		speed = 0;
	}

	if (speed > maxSpeed) {
		speed = maxSpeed;
	}

	LivingEntity::Update();
}

void PlayerEntity::Collect(ItemEntity* item)
{
	// in the future we might add this item to our inventory (e.g. weapon, tradable item).
	// for now items are consumables that just change our stats

	LivingStats* statsDelta = item->Consume();
	this->mStats->attack += statsDelta->attack;
	this->mStats->maxHealth += statsDelta->maxHealth;
	this->mStats->health += statsDelta->health;
	this->mStats->speed += statsDelta->speed;
	if (this->mStats->health > this->mStats->maxHealth)
	{
		this->mStats->health = this->mStats->maxHealth;
	}
}
