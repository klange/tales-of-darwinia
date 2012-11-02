#include <stdio.h>
#include "playerentity.h"
#include "audiomanager.h"
#include "inputmanager.h"
#include "maps.h"
#include "math.h"

#define SFX_PLAYER_MOVE SFX_DOG_BARK

PlayerEntity* gpPlayerEntity = NULL;

void blitText(const char* text, int len);

void PlayerEntity::Init(){
	LivingEntity::Init();

	type = PLAYERENTITY;
	// TODO: Make this more robust
	mStats->attack = 1;
}

PlayerEntity::PlayerEntity(SpriteData* gfx, LivingStats* stats) : LivingEntity(gfx, stats)
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

	int mapX = gpMapEngine->getScrollX();
	int mapY = gpMapEngine->getScrollY();

	if (keysHeld() & KEY_TOUCH) {
		touchPosition curTouchPosition;
		touchRead(&curTouchPosition);
		setTargetPosition(Vector3<s16>(mapX + curTouchPosition.px, mapY + curTouchPosition.py, 1));
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

	const int slop = 32;
	const int width = 256;
	const int height = 190;

	const int scrollSpeed = 2;
	int relX = 0;
	int relY = 0;

	if (position.x() - mapX < slop)
	{
		relX = -scrollSpeed;
	}
	if (mapX + width - position.x() < slop) {
		relX = scrollSpeed;
	}
	if (position.y() - mapY < slop) {
		relY = -scrollSpeed;
	}
	if (mapY + height - position.y() < slop) {
		relY = scrollSpeed;
	}

	gpMapEngine->scrollMapRelative(gMapTileIndex, relX, relY);
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
	mStats->points += statsDelta->points;
	if (mStats->health > mStats->maxHealth)
	{
		mStats->health = mStats->maxHealth;
	}
	if (mStats->health <= 0)
		mStats->health = 0;
	if (mStats->attack <= 1)
		mStats->attack = 1;
	if (mStats->speed <= 1)
		mStats->speed = 1;
	if (mStats->points <= 0)
		mStats->points = 0;

	BlitStatus();

	if (mStats->health <= 0)
	{
		audioManager.playSound(SFX_GAME_OVER);
		audioManager.pauseMusic();
		OnDeath();
	}
	else
	{
		if (statsDelta->health < 0)
		{
			audioManager.playSound(SFX_CHOKE);
		}
		else
		{
			audioManager.playSound(SFX_CHOMP);
		}
	}
}

void PlayerEntity::BlitStatus()
{
	mStats->Print("DARWIN");
	char status[17];
	sprintf(status, "%05d      ", mStats->points);
	s16 stars = 5 * mStats->health / mStats->maxHealth;
	for (s16 i = 0; i < 5; i++)
	{
		s16 ixStatus = 10 + i;
		status[ixStatus] = i < stars ? '\1' : '\2';
	}
	status[16] = 0;
	blitText(status, 15);
}


extern bool gReset;

void PlayerEntity::OnDeath()
{
	shouldBeRemoved = true;
	printf("\n\nGAME OVER :-(\n\n");
	gReset = true;
}

EntityType PlayerEntity::getType(){
	return PLAYERENTITY;
}
