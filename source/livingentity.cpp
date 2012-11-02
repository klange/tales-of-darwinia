#include "livingentity.h"
#include "vector3.h"
#include "math.h"
#include <stdio.h>


// this might actually have common methods in it someday

void LivingEntity::Damage(u16 damage){
	mStats->health -= damage;
	if (mStats->health <= 0){
		OnDeath();
	}
}

void LivingEntity::Update(void) {
	directionVector = targetPosition - position;
	u32 magnitude = directionVector.magnitude();

	//float32 total_frames = 200;
	//float32 coefficient = 256.0;

	if (magnitude < 2) {
		return;	
	}

	s16 newx = position.x() + floor(directionVector.x() * speed / magnitude);
	s16 newy = position.y() + floor(directionVector.y() * speed / magnitude);

	Vector3<s16> nextPosition = Vector3<s16>(newx, newy, 1);
	setPosition(nextPosition);

	s16 xComp = abs(directionVector.x());
	s16 yComp = abs(directionVector.y());
	vflip = false;
	hflip = false;

	if (xComp > yComp) {
		if (directionVector.x() < 0) {
			spriteOffset = 1;
			vflip = true;
		} else if (directionVector.x() >= 0) {
			spriteOffset = 1;
		}
	} else {
		if (directionVector.y() < 0) {
			spriteOffset = 0;
		} else if (directionVector.y() >= 0) {
			spriteOffset = 2;
		}
	}
}

void LivingEntity::setTargetPosition(Vector3<s16> tar) {
	targetPosition = tar;
}

Vector3<s16> LivingEntity::getTargetPosition(void) {
	return targetPosition;
}
