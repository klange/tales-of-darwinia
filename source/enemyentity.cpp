#include "enemyentity.h"
#include "inputmanager.h"
#include "playerentity.h"
#include "audiomanager.h"

#include <stdio.h>

void EnemyEntity::Update()
{

	if(shouldBeRemoved)
		return;

	speed = 2;

	if (IsTouchedByNearbyPlayer())
	{
		audioManager.playSound(SFX_OUCH);
		LivingEntity::Damage(gpPlayerEntity->mStats->attack);
		printf("Ouch %d!\n", mStats->health);
	}

	this->setTargetPosition(gpPlayerEntity->position);

	LivingEntity::Update();
}

void EnemyEntity::OnDeath(){
	shouldBeRemoved = true;
	hidden = true;
}
