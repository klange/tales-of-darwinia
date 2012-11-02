#include "livingentity.h"
#include "vector3.h"
#include "math.h"
#include <stdio.h>


// this might actually have common methods in it someday
void LivingEntity::Init(){
	Entity::Init();
	
	// Make this more robust, read from a map or something later
	mStats = new LivingStats(8, 1, 0, 8, 8);
}

void LivingEntity::Damage(u16 damage){
	if (damage >= mStats->health){
		mStats->health = 0;
		OnDeath();
	} else {
		mStats->health -= damage;
	}
}

void LivingEntity::Update(void) {
	directionVector = targetPosition - position;
	float32 magnitude = (float32)directionVector.magnitude();

	if (magnitude < 1.5) {
		movementState = STOPPED;
		return;
	}

	float32 diffx = ((float32)abs(directionVector.x()) / magnitude) * speed;
	float32 diffy = ((float32)abs(directionVector.y()) / magnitude) * speed;

	float32 newx = 0;
	if (directionVector.x() < 0) {
		newx = (float32)position.x() - diffx;
	} else {
		newx = (float32)position.x() + diffx;
	}

	float32 newy = 0;
	if (directionVector.y() < 0) {
		newy = (float32)position.y() - diffy;
	} else {
		newy = (float32)position.y() + diffy;
	}

	s16 x = 0;
	s16 y = 0;
	if (directionVector.x() < 0) {
		x = ceil(newx);
	} else {
		x = floor(newx);
	}

	if (directionVector.y() < 0) {
		y = ceil(newy);
	} else {
		y = floor(newy);
	}

	setPosition(Vector3<s16>(x, y, 1));

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
