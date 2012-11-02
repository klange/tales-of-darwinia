#include <stdio.h>
#include "playerentity.h"
#include "audiomanager.h"
#include "inputmanager.h"
#include "maps.h"
#include "math.h"

#define SFX_PLAYER_MOVE SFX_DOG_BARK

PlayerEntity* gpPlayerEntity = NULL;

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
	this->mStats->attack += statsDelta->attack;
	this->mStats->maxHealth += statsDelta->maxHealth;
	this->mStats->health += statsDelta->health;
	this->mStats->speed += statsDelta->speed;
	if (this->mStats->health > this->mStats->maxHealth)
	{
		this->mStats->health = this->mStats->maxHealth;
	}

	mStats->Print("DARWIN");

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

void PlayerEntity::OnDeath()
{
	shouldBeRemoved = true;
	printf("\n\nGAME OVER :-(\n\n");
}
