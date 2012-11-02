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
}

PlayerEntity::~PlayerEntity()
{
	gpPlayerEntity = NULL;
}


void PlayerEntity::Update()
{
	speed = 3.0;
	if (keysHeld() & KEY_TOUCH) {
		touchPosition curTouchPosition;
		touchRead(&curTouchPosition);
		setTargetPosition(Vector3<s16>(curTouchPosition.px, curTouchPosition.py, 1));
	}
	s16 magnitude = directionVector.magnitude();
	s16 xComp = abs(directionVector.x()/magnitude);
	s16 yComp = abs(directionVector.y()/magnitude);

	if (xComp > yComp) {
		if (directionVector.x() < 0) {
			spriteOffset = 1;
			vflip = true;
			hflip = false;
		} else if (directionVector.x() >= 0) {
			spriteOffset = 1;
			vflip = false;
			hflip = false;	
		}
	} else {
		if (directionVector.y() < 0) {
			spriteOffset = 0;
			vflip = false;
			hflip = false;
		} else if (directionVector.y() >= 0) {
			spriteOffset = 2;
			vflip = false;
			hflip = false;
		}
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
