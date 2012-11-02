#include <stdio.h>
#include "playerentity.h"
#include "audiomanager.h"
#include "inputmanager.h"
#include "math.h"

#define SFX_PLAYER_MOVE SFX_DOG_BARK

PlayerEntity* gpPlayerEntity = NULL;

void blitText(const char* text, int len);

void PlayerEntity::Init(){
	LivingEntity::Init();

	// TODO: Make this more robust
	mStats->attack = 1;
}

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
	if (shouldBeRemoved)
		return;

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
	mStats->attack += statsDelta->attack;
	mStats->maxHealth += statsDelta->maxHealth;
	mStats->health += statsDelta->health;
	mStats->speed += statsDelta->speed;
	if (mStats->health > mStats->maxHealth)
	{
		mStats->health = mStats->maxHealth;
	}
	if (mStats->health <= 0)
	{
		mStats->health = 0;
	}

	mStats->Print("DARWIN");
	BlitStatus();

	if (mStats->health <= 0)
	{
		audioManager.playSound(SFX_GAME_OVER);
		audioManager.pauseMusic();
		OnDeath();
	}
	else
	{
		audioManager.playSound(SFX_CHOMP);
	}
}

void PlayerEntity::BlitStatus()
{
	char status[17];
	sprintf(status, "%05d      ", mStats->points);
	s16 stars = 5 * mStats->health / mStats->maxHealth;
	printf("stars: %d\n", stars);
	for (s16 i = 0; i < 5; i++)
	{
		s16 ixStatus = 10 + i;
//		status[ixStatus] = i < stars ? '\1' : '\2';
		status[ixStatus] = i < stars ? '*' : '-';
	}
	status[16] = 0;
	printf("%s\n", status);
	blitText(status, 15);
}

void PlayerEntity::OnDeath()
{
	shouldBeRemoved = true;
	printf("\n\nGAME OVER :-(\n\n");
}
