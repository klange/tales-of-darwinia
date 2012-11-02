#include "livingentity.h"


// this might actually have common methods in it someday

void LivingEntity::Damage(u16 damage){
	mStats.health -= damage;
	if (mStats.health <= 0){
		OnDeath();
	}
}
